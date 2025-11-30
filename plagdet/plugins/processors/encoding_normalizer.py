"""Encoding normalization processor plugin for handling non-UTF-8 files."""

from pathlib import Path
from typing import Any, Dict, List, Tuple

import chardet
from pydantic import BaseModel

from ..base import ProcessorPlugin
from ..models.processors import EncodingNormalizerConfig
from ...core.registry import register_processor
from ...ui.formatters import print_info, print_success, print_warning


@register_processor
class EncodingNormalizer(ProcessorPlugin):
    """Pre-processor to normalize file encodings to UTF-8 and validate submissions."""

    # Specify expected config type for validation
    CONFIG_TYPE = EncodingNormalizerConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "encoding_normalizer"

    def process(self, context: Dict[str, Any], config: BaseModel) -> Dict[str, Any]:
        """Normalize file encodings and validate submissions.

        Args:
            context: Pipeline context containing target_path
            config: EncodingNormalizerConfig with extensions to process

        Returns:
            Updated context (unchanged, but files are converted in-place)
        """
        target_path = Path(context.get('target_path', ''))
        if not target_path.exists():
            return context

        # Type-safe config access
        enc_config = (
            config
            if isinstance(config, EncodingNormalizerConfig)
            else EncodingNormalizerConfig(**config.model_dump())
        )

        print_info(f"Checking file encodings for extensions: {enc_config.extensions}")

        # Track encoding conversions
        converted = 0
        for ext in enc_config.extensions:
            for file_path in target_path.rglob(f'*.{ext}'):
                if self._normalize_file(file_path):
                    converted += 1

        if converted:
            print_success(f"Converted {converted} files to UTF-8")

        # Validate submissions and report issues
        wrong_extensions, empty_submissions = self._validate_submissions(
            target_path, enc_config.extensions
        )

        if wrong_extensions or empty_submissions:
            self._write_validation_report(target_path, wrong_extensions, empty_submissions)

        return context

    def _normalize_file(self, file_path: Path) -> bool:
        """Normalize a single file to UTF-8 encoding.

        Args:
            file_path: Path to file to normalize

        Returns:
            True if file was converted, False otherwise
        """
        try:
            raw = file_path.read_bytes()
            detected = chardet.detect(raw)
            encoding = detected.get('encoding', 'utf-8')

            if encoding and encoding.lower() not in ('utf-8', 'ascii'):
                try:
                    content = raw.decode(encoding)
                    file_path.write_text(content, encoding='utf-8')
                    print_info(f"Converted {file_path.parent.name}/{file_path.name}: {encoding} -> UTF-8")
                    return True
                except Exception as e:
                    print_warning(f"Could not convert {file_path.name}: {e}")
        except Exception as e:
            print_warning(f"Could not read {file_path.name}: {e}")

        return False

    def _validate_submissions(
        self, target_path: Path, extensions: List[str]
    ) -> Tuple[List[Tuple[str, List[str]]], List[str]]:
        """Validate student submissions for correct file extensions.

        Args:
            target_path: Root directory containing student folders
            extensions: Expected file extensions

        Returns:
            Tuple of (wrong_extensions, empty_submissions) lists
        """
        # Directories to skip (not student submissions)
        excluded_dirs = {'base', 'results', 'dolos-report'}

        wrong_extensions: List[Tuple[str, List[str]]] = []
        empty_submissions: List[str] = []

        for student_dir in target_path.iterdir():
            # Skip hidden directories (e.g., .git, .venv)
            if student_dir.name.startswith('.'):
                continue
            if not student_dir.is_dir() or student_dir.name in excluded_dirs:
                continue

            # Check if student has any expected files
            expected_files = []
            for ext in extensions:
                expected_files.extend(student_dir.glob(f'*.{ext}'))

            if not expected_files:
                # Check what they did submit
                other_files = [f.name for f in student_dir.iterdir() if f.is_file()]
                if other_files:
                    wrong_extensions.append((student_dir.name, other_files))
                else:
                    empty_submissions.append(student_dir.name)

        return wrong_extensions, empty_submissions

    def _write_validation_report(
        self,
        target_path: Path,
        wrong_ext: List[Tuple[str, List[str]]],
        empty: List[str],
    ) -> None:
        """Write validation report for submission issues.

        Args:
            target_path: Root directory
            wrong_ext: List of (student_name, [files]) with wrong extensions
            empty: List of student names with empty submissions
        """
        results_dir = target_path / 'results'
        results_dir.mkdir(parents=True, exist_ok=True)
        report_path = results_dir / 'submission_issues.txt'

        with open(report_path, 'w', encoding='utf-8') as f:
            if wrong_ext:
                f.write("=== WRONG FILE EXTENSIONS ===\n")
                for student, files in wrong_ext:
                    f.write(f"{student}: {', '.join(files)}\n")
                f.write("\n")

            if empty:
                f.write("=== EMPTY SUBMISSIONS ===\n")
                for student in empty:
                    f.write(f"{student}\n")

        print_warning(f"Found {len(wrong_ext)} wrong extensions, {len(empty)} empty submissions")
        print_info(f"See: {report_path}")
