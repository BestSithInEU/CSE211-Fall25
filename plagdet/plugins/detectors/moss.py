"""MOSS (Measure of Software Similarity) plagiarism detection plugin."""

import glob
import os
import re
from pathlib import Path
from typing import List

from pydantic import BaseModel

from ...core.models.detection import DetectionResult
from ..base import DetectorPlugin
from ..models.detectors import MossConfig
from ...core.registry import register_detector
from ...ui.formatters import print_error, print_info, print_success, print_warning

try:
    import mosspy
    MOSS_AVAILABLE = True
except ImportError:
    MOSS_AVAILABLE = False


@register_detector
class MossDetector(DetectorPlugin):
    """MOSS plagiarism detection tool integration.

    Requires:
        - mosspy package (pip install mosspy)
        - Valid MOSS user ID from Stanford

    Privacy Warning:
        MOSS sends code to Stanford's external server.
        Results are publicly accessible via URL.
    """

    # Specify expected config type for validation
    CONFIG_TYPE = MossConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "moss"

    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Run MOSS detection on submissions.

        Args:
            target_path: Path to directory containing submissions
            config: MossConfig with detection parameters

        Returns:
            DetectionResult with MOSS comparison results

        Raises:
            RuntimeError: If mosspy not installed or MOSS fails
        """
        if not MOSS_AVAILABLE:
            raise RuntimeError(
                "mosspy not installed. Install with: pip install mosspy"
            )

        # Type-safe config access
        moss_config = config if isinstance(config, MossConfig) else MossConfig(**config.model_dump())

        # Pydantic already validated userid is not empty
        language = moss_config.language
        extensions = moss_config.extensions
        base_files = moss_config.base_files
        max_matches = moss_config.max_matches

        print_warning("⚠️  MOSS sends code to external server (Stanford)")
        print_info(f"Running MOSS for language {language}...")

        # Initialize MOSS
        moss = mosspy.Moss(moss_config.userid, language)
        moss.setIgnoreLimit(max_matches)

        target_path_str = str(target_path)

        # Add base code directory files if base_path is set
        if moss_config.base_path:
            base_dir = os.path.join(target_path_str, moss_config.base_path)
            if os.path.isdir(base_dir):
                for ext in extensions:
                    for f in glob.glob(os.path.join(base_dir, f"**/*.{ext}"), recursive=True):
                        moss.addBaseFile(f)
                        print_info(f"Added base file: {os.path.basename(f)}")

        # Add individual base files (legacy support)
        for base_file in base_files:
            base_file_path = os.path.join(target_path_str, base_file)
            if os.path.exists(base_file_path):
                moss.addBaseFile(base_file_path)
                print_info(f"Added base file: {base_file}")

        # Add submission files
        file_count = 0
        for ext in extensions:
            pattern = os.path.join(target_path_str, f"**/*.{ext}")
            for file_path in glob.glob(pattern, recursive=True):
                moss.addFile(file_path)
                file_count += 1

        if file_count == 0:
            raise RuntimeError(f"No files found matching extensions: {extensions}")

        print_info(f"Submitting {file_count} files to MOSS...")

        # Submit to MOSS
        try:
            url = moss.send()
            print_success(f"MOSS report URL: {url}")
        except Exception as e:
            raise RuntimeError(f"MOSS submission failed: {e}")

        # Parse results from URL
        comparisons = self._parse_moss_results(url)

        return DetectionResult(
            comparisons=comparisons,
            metadata={
                'tool': 'moss',
                'language': language,
                'report_url': url,
                'files_submitted': file_count
            },
            raw_data={'url': url}
        )

    def _get_default_extension(self, language: str) -> str:
        """Get default file extension for language."""
        extensions = {
            'c': 'c',
            'cc': 'cpp',
            'java': 'java',
            'python': 'py',
            'javascript': 'js',
            'csharp': 'cs',
        }
        return extensions.get(language, language)

    def _parse_moss_results(self, url: str) -> List[dict]:
        """Parse MOSS HTML results to extract comparisons.

        Args:
            url: MOSS report URL

        Returns:
            List of comparison dictionaries
        """
        try:
            import urllib.request
            from html.parser import HTMLParser

            # Fetch HTML
            with urllib.request.urlopen(url) as response:
                html = response.read().decode('utf-8')

            # Parse HTML to extract comparisons
            comparisons = []

            # MOSS HTML structure: <TR><TD><A HREF="...">file1 (X%)</A>
            #                      <TD><A HREF="...">file2 (Y%)</A>
            pattern = r'<TR><TD><A HREF="[^"]+">([^<]+) \((\d+)%\)</A>\s*<TD><A HREF="[^"]+">([^<]+) \((\d+)%\)</A>'

            for match in re.finditer(pattern, html):
                file1 = match.group(1).strip()
                sim1 = int(match.group(2))
                file2 = match.group(3).strip()
                sim2 = int(match.group(4))

                # Extract student folder name (parent of the file)
                left_path = Path(file1)
                right_path = Path(file2)
                left_name = left_path.parent.name
                right_name = right_path.parent.name

                comparisons.append({
                    'first_submission': left_name,
                    'second_submission': right_name,
                    'similarity': max(sim1, sim2) / 100.0,  # Use max similarity
                    'metric': 'MOSS',
                    'similarity1': sim1 / 100.0,
                    'similarity2': sim2 / 100.0
                })

            return comparisons

        except Exception as e:
            print_warning(f"Failed to parse MOSS results: {e}")
            print_info("Results available at URL, but parsing failed")
            return []
