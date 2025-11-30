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
        self._run_jplag(
            str(target_path),
            jplag_config.language,
            jplag_config.token_length,
            jplag_config.base_path,
            jplag_config.subdirectory,
            jplag_config.suffixes,
            jplag_config.exclude_files,
            jplag_config.min_token_match
        )

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

    def _run_jplag(
        self,
        target_path: str,
        language: str,
        token_length: int,
        base_path: Optional[str] = None,
        subdirectory: Optional[str] = None,
        suffixes: Optional[list[str]] = None,
        exclude_files: Optional[list[str]] = None,
        min_token_match: Optional[int] = None
    ) -> None:
        """Execute JPlag command.

        Args:
            target_path: Path to submissions
            language: Programming language
            token_length: Minimum token length
            base_path: Optional base code path
            subdirectory: Optional subdirectory within submissions
            suffixes: Optional file suffixes to include
            exclude_files: Optional file patterns to exclude
            min_token_match: Optional minimum number of tokens for a match
        """
        jplag_command = [
            "java",
            "-jar",
            "./jplag.jar",
            "-l",
            language,
            "-t",
            str(token_length),
            os.path.abspath(target_path)
        ]

        if base_path:
            full_base_path = os.path.join(target_path, base_path)
            jplag_command.extend(["-bc", os.path.abspath(full_base_path)])
            print_info(f"Using base code: {base_path}")

        if subdirectory:
            jplag_command.extend(["-s", subdirectory])

        if suffixes:
            jplag_command.extend(["-p", ",".join(suffixes)])

        if exclude_files:
            jplag_command.extend(["-x", ",".join(exclude_files)])

        if min_token_match:
            jplag_command.extend(["-m", str(min_token_match)])

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
        result_zip = "result.zip"

        if not os.path.exists(result_zip):
            raise FileNotFoundError("JPlag did not generate result.zip")

        # Extract results to temp directory (not 'results' to avoid conflict with output dir)
        results_dir = Path(target_path) / ".jplag_temp"
        results_dir.mkdir(exist_ok=True)

        with zipfile.ZipFile(result_zip, 'r') as zip_ref:
            zip_ref.extractall(results_dir)

        # Load overview.json
        overview_path = results_dir / "overview.json"
        if not overview_path.exists():
            raise FileNotFoundError("overview.json not found in results")

        with open(overview_path, 'r', encoding='utf-8') as f:
            data = json.load(f)

        # Parse comparisons into Pydantic Comparison objects
        comparisons = []
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
        # Move result.zip to target directory
        result_zip = "result.zip"
        if os.path.exists(result_zip):
            target_zip = Path(target_path) / result_zip
            if target_zip.exists():
                target_zip.unlink()
            shutil.move(result_zip, target_path)

        # Remove extracted temp directory
        results_dir = Path(target_path) / ".jplag_temp"
        if results_dir.exists():
            shutil.rmtree(results_dir)
