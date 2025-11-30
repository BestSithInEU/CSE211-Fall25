"""CopyDetect plagiarism detection plugin."""

import os
from pathlib import Path
from typing import List

from pydantic import BaseModel

from ...core.models.detection import DetectionResult
from ..base import DetectorPlugin
from ..models.detectors import CopyDetectConfig
from ...core.registry import register_detector
from ...ui.formatters import print_info, print_success

try:
    from copydetect import CopyDetector
    COPYDETECT_AVAILABLE = True
except ImportError:
    COPYDETECT_AVAILABLE = False


@register_detector
class CopyDetectDetector(DetectorPlugin):
    """CopyDetect plagiarism detection tool integration.

    Requires:
        - copydetect package (pip install copydetect)

    CopyDetect is a Python-based code plagiarism detection tool
    that generates HTML reports with highlighted matches.
    """

    # Specify expected config type for validation
    CONFIG_TYPE = CopyDetectConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "copydetect"

    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Run CopyDetect detection on submissions.

        Args:
            target_path: Path to directory containing submissions
            config: CopyDetectConfig with detection parameters

        Returns:
            DetectionResult with CopyDetect comparison results

        Raises:
            RuntimeError: If copydetect not installed or execution fails
        """
        if not COPYDETECT_AVAILABLE:
            raise RuntimeError(
                "copydetect not installed. Install with: pip install copydetect"
            )

        # Type-safe config access
        cd_config = config if isinstance(config, CopyDetectConfig) else CopyDetectConfig(**config.model_dump())

        extensions = cd_config.extensions
        reference_dirs = cd_config.reference_dirs
        boilerplate_dirs = cd_config.boilerplate_dirs
        display_threshold = cd_config.display_threshold
        noise_threshold = cd_config.noise_threshold

        print_info(f"Running CopyDetect with extensions: {extensions}...")

        target_path_str = str(target_path)

        # Add base_path to boilerplate_dirs if set
        if cd_config.base_path:
            base_dir = os.path.join(target_path_str, cd_config.base_path)
            if os.path.isdir(base_dir):
                boilerplate_dirs = list(boilerplate_dirs) + [base_dir]
                print_info(f"Added base code directory: {cd_config.base_path}")

        # Get all student subdirectories as test directories
        # CopyDetect works better when given explicit directories
        student_dirs = []
        for item in Path(target_path_str).iterdir():
            if item.is_dir() and item.name != cd_config.base_path:
                student_dirs.append(str(item))

        # Use student directories if found, otherwise use target path
        test_dirs = student_dirs if student_dirs else [target_path_str]
        ref_dirs = test_dirs + reference_dirs

        print_info(f"Found {len(test_dirs)} submission directories")

        # Initialize CopyDetector (note: parameter is ref_dirs not reference_dirs)
        try:
            detector = CopyDetector(
                test_dirs=test_dirs,
                ref_dirs=ref_dirs,
                boilerplate_dirs=boilerplate_dirs,
                extensions=extensions,
                noise_t=noise_threshold,
                display_t=display_threshold,
                autoopen=False,
                silent=True
            )

            # Run detection
            detector.run()

            # Extract results
            comparisons = self._extract_results(detector, display_threshold)

            print_success(f"CopyDetect analysis completed: {len(comparisons)} comparisons")

            return DetectionResult(
                comparisons=comparisons,
                metadata={
                    'tool': 'copydetect',
                    'extensions': extensions,
                    'display_threshold': display_threshold,
                    'total_comparisons': len(comparisons)
                },
                raw_data={'detector': detector}
            )

        except Exception as e:
            raise RuntimeError(f"CopyDetect execution failed: {e}")

    def _extract_results(self, detector: 'CopyDetector', threshold: float) -> List[dict]:
        """Extract comparison results from CopyDetector.

        Args:
            detector: CopyDetector instance
            threshold: Minimum similarity threshold

        Returns:
            List of comparison dictionaries
        """
        comparisons = []

        try:
            # CopyDetect returns tuples: [sim1, sim2, file1_path, file2_path, code1, code2, overlap]
            for result in detector.get_copied_code_list():
                sim1 = float(result[0])  # Similarity for file1
                sim2 = float(result[1])  # Similarity for file2
                file1_path = result[2]   # File path string
                file2_path = result[3]   # File path string

                # Use max similarity
                similarity = max(sim1, sim2)

                # Filter by threshold
                if similarity >= threshold:
                    # Extract student folder name (parent of the file)
                    left_name = Path(file1_path).parent.name
                    right_name = Path(file2_path).parent.name

                    comparisons.append({
                        'first_submission': left_name,
                        'second_submission': right_name,
                        'similarity': similarity,
                        'metric': 'COPYDETECT'
                    })

        except Exception as e:
            print_info(f"Failed to extract CopyDetect results: {e}")

        return comparisons
