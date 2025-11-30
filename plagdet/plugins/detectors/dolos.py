"""Dolos plagiarism detection plugin."""

import glob
import os
import shutil
import subprocess
from pathlib import Path
from typing import List

from pydantic import BaseModel

from ...core.models.detection import DetectionResult
from ..base import DetectorPlugin
from ..models.detectors import DolosConfig
from ...core.registry import register_detector
from ...ui.formatters import print_error, print_info, print_success

try:
    import pandas as pd
    PANDAS_AVAILABLE = True
except ImportError:
    PANDAS_AVAILABLE = False


@register_detector
class DolosDetector(DetectorPlugin):
    """Dolos plagiarism detection tool integration.

    Requires:
        - Node.js and npm
        - Dolos CLI: npm install -g @dodona/dolos
        - pandas package for CSV parsing

    Dolos is a modern, open-source plagiarism detection tool
    with a beautiful web interface and CSV export.
    """

    # Specify expected config type for validation
    CONFIG_TYPE = DolosConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "dolos"

    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Run Dolos detection on submissions.

        Args:
            target_path: Path to directory containing submissions
            config: DolosConfig with detection parameters

        Returns:
            DetectionResult with Dolos comparison results

        Raises:
            RuntimeError: If Dolos not installed or execution fails
        """
        if not PANDAS_AVAILABLE:
            raise RuntimeError(
                "pandas not installed. Install with: pip install pandas"
            )

        # Check if Dolos is installed
        if not shutil.which("dolos"):
            raise RuntimeError(
                "Dolos not installed. Install with: npm install -g @dodona/dolos"
            )

        # Type-safe config access
        dolos_config = config if isinstance(config, DolosConfig) else DolosConfig(**config.model_dump())

        language = dolos_config.language
        file_pattern = dolos_config.file_pattern or self._get_default_pattern(language)
        min_similarity = dolos_config.min_similarity

        # Make output directory relative to target path for multi-project support
        target_path_obj = Path(target_path)
        output_dir = str(target_path_obj / dolos_config.output_dir)

        # Clean up old report directory if exists
        if Path(output_dir).exists():
            shutil.rmtree(output_dir)

        print_info(f"Running Dolos for language {language}...")

        target_path_str = str(target_path)

        # Build file path pattern and expand glob
        full_pattern = os.path.join(target_path_str, file_pattern)

        # Expand glob pattern to get actual file list
        files = glob.glob(full_pattern, recursive=True)

        # Exclude files in base_path directory if set
        if dolos_config.base_path:
            base_dir = os.path.join(target_path_str, dolos_config.base_path)
            base_dir_normalized = os.path.normpath(base_dir)
            files = [f for f in files if not os.path.normpath(f).startswith(base_dir_normalized)]
            print_info(f"Excluding base code from: {dolos_config.base_path}")

        if not files:
            raise RuntimeError(f"No files found matching pattern: {full_pattern}")

        print_info(f"Found {len(files)} files to analyze")

        # Run Dolos CLI with CSV output
        try:
            result = subprocess.run(
                [
                    "dolos", "run",
                    "-f", "csv",
                    "--language", language,
                    "-o", output_dir
                ] + files,  # Add all matched files
                capture_output=True,
                text=True,
                check=True
            )

            if result.stderr:
                print_info(f"Dolos output: {result.stderr}")

        except subprocess.CalledProcessError as e:
            raise RuntimeError(f"Dolos execution failed: {e.stderr}")
        except FileNotFoundError:
            raise RuntimeError("Dolos executable not found")

        # Parse CSV results
        pairs_file = Path(output_dir) / "pairs.csv"
        if not pairs_file.exists():
            raise RuntimeError(f"Dolos output file not found: {pairs_file}")

        comparisons = self._parse_dolos_csv(pairs_file, min_similarity)

        print_success(f"Dolos analysis completed: {len(comparisons)} comparisons")

        return DetectionResult(
            comparisons=comparisons,
            metadata={
                'tool': 'dolos',
                'language': language,
                'output_dir': output_dir,
                'total_comparisons': len(comparisons)
            },
            raw_data={'output_dir': output_dir}
        )

    def _get_default_pattern(self, language: str) -> str:
        """Get default file pattern for language."""
        patterns = {
            'python': '**/*.py',
            'java': '**/*.java',
            'javascript': '**/*.js',
            'typescript': '**/*.ts',
            'c': '**/*.c',
            'cpp': '**/*.cpp',
            'csharp': '**/*.cs',
        }
        return patterns.get(language, f'**/*.{language}')

    def _parse_dolos_csv(self, pairs_file: Path, min_similarity: float) -> List[dict]:
        """Parse Dolos pairs.csv output.

        Args:
            pairs_file: Path to pairs.csv
            min_similarity: Minimum similarity threshold

        Returns:
            List of comparison dictionaries
        """
        try:
            # Read CSV
            df = pd.read_csv(pairs_file)

            # Filter by similarity
            df = df[df['similarity'] >= min_similarity]

            # Convert to comparison format
            comparisons = []
            for _, row in df.iterrows():
                # Extract student folder name (parent of the file)
                left_path = Path(row['leftFilePath'])
                right_path = Path(row['rightFilePath'])
                left_name = left_path.parent.name
                right_name = right_path.parent.name

                comparisons.append({
                    'first_submission': left_name,
                    'second_submission': right_name,
                    'similarity': float(row['similarity']),
                    'metric': 'DOLOS',
                    'longest_fragment': int(row.get('longestFragment', 0)),
                    'total_overlap': int(row.get('totalOverlap', 0))
                })

            return comparisons

        except Exception as e:
            raise RuntimeError(f"Failed to parse Dolos CSV: {e}")
