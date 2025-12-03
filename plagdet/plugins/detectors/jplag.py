"""JPlag plagiarism detection plugin."""

import json
import os
import shutil
import subprocess
import zipfile
from pathlib import Path
from typing import Optional

from pydantic import BaseModel

from ...core.models.detection import Comparison, DetectionResult
from ..base import DetectorPlugin
from ..models.detectors import JPlagConfig
from ...core.registry import register_detector
from ...ui.formatters import print_info, print_success


@register_detector
class JPlagDetector(DetectorPlugin):
    """JPlag plagiarism detection tool integration."""

    # Specify expected config type for validation
    CONFIG_TYPE = JPlagConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "jplag"

    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Run JPlag detection on submissions.

        Args:
            target_path: Path to directory containing submissions
            config: JPlagConfig with detection parameters

        Returns:
            DetectionResult (Pydantic model) with JPlag comparison results

        Raises:
            DetectionError: If detection process fails
        """
        # Type-safe config access - Pydantic ensures these fields exist
        jplag_config = config if isinstance(config, JPlagConfig) else JPlagConfig(**config.model_dump())

        print_info(f"Running JPlag for language {jplag_config.language}...")

        # Run JPlag
        self._run_jplag(str(target_path), jplag_config)

        # Load and parse results (returns list of Comparison objects)
        comparisons, raw_data = self._load_results(str(target_path))

        # Clean up result files
        self._cleanup_results(str(target_path))

        print_success("JPlag detection completed")

        return DetectionResult(
            comparisons=comparisons,
            metadata={
                'tool': 'jplag',
                'language': jplag_config.language,
                'token_length': jplag_config.token_length
            },
            raw_data=raw_data
        )

    def _run_jplag(self, target_path: str, config: JPlagConfig) -> None:
        """Execute JPlag command.

        Args:
            target_path: Path to submissions
            config: JPlagConfig with all detection parameters
        """
        # Use unique result filename to avoid conflicts with existing 'results' folders
        result_name = ".jplag_results"
        jplag_command = [
            "java",
            "-jar",
            "./jplag.jar",
            "-M", "RUN",  # Force RUN mode (don't start viewer)
            "-r", result_name,  # Unique result filename
            "-l",
            config.language,
            "-t",
            str(config.token_length),
            os.path.abspath(target_path)
        ]

        # Base code directory
        if config.base_path:
            full_base_path = os.path.join(target_path, config.base_path)
            jplag_command.extend(["-bc", os.path.abspath(full_base_path)])
            print_info(f"Using base code: {config.base_path}")

        # Subdirectory within submissions
        if config.subdirectory:
            jplag_command.extend(["-s", config.subdirectory])

        # File suffixes to include
        if config.suffixes:
            jplag_command.extend(["-p", ",".join(config.suffixes)])

        # Files to exclude (JPlag expects a file path, not a list)
        if config.exclude_files:
            exclude_file = Path(target_path) / ".jplag_exclude"
            exclude_file.write_text("\n".join(config.exclude_files))
            jplag_command.extend(["-x", str(exclude_file)])

        # Minimum token match
        if config.min_token_match:
            jplag_command.extend(["--min-tokens", str(config.min_token_match)])

        # Token normalization (catches variable renaming)
        if config.normalize:
            jplag_command.append("--normalize")
            print_info("Token normalization enabled")

        # Match merging options (catches obfuscation)
        if config.match_merging:
            jplag_command.append("--match-merging")
            print_info("Match merging enabled (obfuscation detection)")

        if config.gap_size is not None:
            jplag_command.extend(["--gap-size", str(config.gap_size)])

        if config.neighbor_length is not None:
            jplag_command.extend(["--neighbor-length", str(config.neighbor_length)])

        if config.required_merges is not None:
            jplag_command.extend(["--required-merges", str(config.required_merges)])

        # Clustering options
        if config.cluster_skip:
            jplag_command.append("--cluster-skip")

        if config.cluster_algorithm:
            jplag_command.extend(["--cluster-alg", config.cluster_algorithm.upper()])

        if config.cluster_metric:
            jplag_command.extend(["--cluster-metric", config.cluster_metric.upper()])

        # Output options
        if config.similarity_threshold is not None:
            jplag_command.extend(["-m", str(config.similarity_threshold)])

        if config.shown_comparisons is not None:
            jplag_command.extend(["-n", str(config.shown_comparisons)])

        if config.csv_export:
            jplag_command.append("--csv-export")

        # Directory modes for old vs new submissions
        if config.new_directories:
            for new_dir in config.new_directories:
                jplag_command.extend(["-new", os.path.abspath(new_dir)])

        if config.old_directories:
            for old_dir in config.old_directories:
                jplag_command.extend(["-old", os.path.abspath(old_dir)])

        # Additional options
        if config.encoding:
            jplag_command.extend(["--encoding", config.encoding])

        if config.debug:
            jplag_command.append("-d")

        if config.overwrite:
            jplag_command.append("--overwrite")

        if config.result_file:
            jplag_command.extend(["-r", config.result_file])

        try:
            subprocess.run(
                jplag_command,
                check=True,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.PIPE
            )
        except subprocess.CalledProcessError as e:
            raise RuntimeError(f"JPlag execution failed: {e.stderr.decode()}")

    def _load_results(self, target_path: str) -> tuple[list[Comparison], dict]:
        """Load and parse JPlag results.

        Args:
            target_path: Path to submissions

        Returns:
            Tuple of (list of Comparison objects, raw data dict)
        """
        # JPlag v6.x uses ".jplag" extension, v5.x uses ".zip"
        # We use ".jplag_results" as our custom name
        result_file = None
        for candidate in [".jplag_results.jplag", ".jplag_results.zip", "results.zip", "result.zip"]:
            if os.path.exists(candidate):
                result_file = candidate
                break

        if not result_file:
            raise FileNotFoundError("JPlag did not generate results.zip")

        # Extract results to temp directory (not 'results' to avoid conflict with output dir)
        results_dir = Path(target_path) / ".jplag_temp"
        results_dir.mkdir(exist_ok=True)

        with zipfile.ZipFile(result_file, 'r') as zip_ref:
            zip_ref.extractall(results_dir)

        # Load results JSON - handle different JPlag versions
        # v6.x uses topComparisons.json, v5.x uses overview.json
        results_json = None
        for json_name in ["topComparisons.json", "overview.json"]:
            json_path = results_dir / json_name
            if json_path.exists():
                results_json = json_path
                break

        if not results_json:
            raise FileNotFoundError("No results JSON found (tried topComparisons.json, overview.json)")

        with open(results_json, 'r', encoding='utf-8') as f:
            data = json.load(f)

        # Parse comparisons into Pydantic Comparison objects
        comparisons = []

        # JPlag v6.x format: topComparisons.json is a JSON array
        if isinstance(data, list):
            for comparison in data:
                try:
                    similarities = comparison.get('similarities', {})
                    # Use AVG similarity by default (already 0-1 scale)
                    avg_similarity = similarities.get('AVG', 0.0)
                    comp = Comparison(
                        first_submission=comparison.get('firstSubmission', ''),
                        second_submission=comparison.get('secondSubmission', ''),
                        similarity=avg_similarity,
                        metric='AVG'
                    )
                    comparisons.append(comp)
                except Exception as e:
                    print_info(f"Skipping invalid comparison: {e}")
                    continue
        # JPlag v5.x format: top_comparisons with similarities dict
        elif 'top_comparisons' in data:
            for comparison in data.get('top_comparisons', []):
                try:
                    similarities = comparison.get('similarities', {})
                    avg_similarity = similarities.get('AVG', 0.0)
                    comp = Comparison(
                        first_submission=comparison.get('first_submission', ''),
                        second_submission=comparison.get('second_submission', ''),
                        similarity=avg_similarity,
                        metric='AVG'
                    )
                    comparisons.append(comp)
                except Exception as e:
                    print_info(f"Skipping invalid comparison: {e}")
                    continue
        # JPlag v3.x/v4.x format: metrics with topComparisons
        else:
            for metric in data.get('metrics', []):
                for comparison in metric.get('topComparisons', []):
                    try:
                        comp = Comparison(
                            first_submission=comparison.get('first_submission', ''),
                            second_submission=comparison.get('second_submission', ''),
                            similarity=comparison.get('similarity', 0.0),
                            metric=metric.get('name', 'UNKNOWN')
                        )
                        comparisons.append(comp)
                    except Exception as e:
                        print_info(f"Skipping invalid comparison: {e}")
                        continue

        return comparisons, data

    def _cleanup_results(self, target_path: str) -> None:
        """Clean up temporary result files.

        Args:
            target_path: Path to submissions
        """
        # Move result file to target directory (handle all naming variants)
        for result_file in [".jplag_results.jplag", ".jplag_results.zip", "results.zip", "result.zip"]:
            if os.path.exists(result_file):
                # Rename to results.zip for consistency
                target_zip = Path(target_path) / "results.zip"
                if target_zip.exists():
                    target_zip.unlink()
                shutil.move(result_file, target_zip)
                break

        # Remove extracted temp directory
        results_dir = Path(target_path) / ".jplag_temp"
        if results_dir.exists():
            shutil.rmtree(results_dir)

        # Remove exclude file if it was created
        exclude_file = Path(target_path) / ".jplag_exclude"
        if exclude_file.exists():
            exclude_file.unlink()
