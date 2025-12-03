"""Handler for utility operations (unzip, cleanup)."""

import re
import shutil
import zipfile
from pathlib import Path
from typing import Optional

import unidecode

from ..services.cleanup import CleanupService
from ..ui.formatters import print_error, print_info, print_success


class UtilityHandler:
    """Handler for utility operations.

    Provides reusable business logic for unzipping archives
    and cleaning up generated files.
    """

    def __init__(self, verbose: bool = False):
        """Initialize handler.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def unzip(self, zip_file: str | Path, output_dir: str | Path) -> None:
        """Extract ZIP archive to output directory.

        Args:
            zip_file: Path to ZIP archive
            output_dir: Directory to extract files to

        Raises:
            FileNotFoundError: If ZIP file doesn't exist
            zipfile.BadZipFile: If file is not a valid ZIP
            IOError: If extraction fails
        """
        zip_path = Path(zip_file)
        output_path = Path(output_dir)

        # Validate ZIP file exists
        if not zip_path.exists():
            raise FileNotFoundError(f"ZIP file not found: {zip_file}")

        # Create output directory
        output_path.mkdir(parents=True, exist_ok=True)

        # Extract
        with zipfile.ZipFile(zip_path, 'r') as zip_ref:
            zip_ref.extractall(output_path)

        # Flatten if single wrapper folder
        self._flatten_if_single_subfolder(output_path)

        # Normalize Moodle-style folder names
        normalized_count = self._normalize_folder_names(output_path)

        if normalized_count > 0:
            print_success(f"Extracted and normalized {normalized_count} submissions to {output_dir}")
        else:
            print_success(f"Extracted submissions to {output_dir}")

    def _flatten_if_single_subfolder(self, output_path: Path) -> None:
        """If extraction created a single wrapper folder, flatten it.

        Common with Moodle exports that wrap everything in a folder.

        Args:
            output_path: Directory to check and flatten
        """
        contents = list(output_path.iterdir())

        # Skip if multiple items, no items, or single item is not a directory
        if len(contents) != 1 or not contents[0].is_dir():
            return

        wrapper = contents[0]

        if self.verbose:
            print_info(f"Flattening wrapper folder: {wrapper.name}")

        # Move all contents up to parent
        for item in wrapper.iterdir():
            dest = output_path / item.name
            if not dest.exists():
                shutil.move(str(item), str(dest))

        # Remove empty wrapper (if empty)
        try:
            wrapper.rmdir()
        except OSError:
            # Not empty, skip removal
            pass

    def _normalize_folder_names(self, output_path: Path) -> int:
        """Normalize Moodle-style folder names to clean format.

        Converts names like "AHMET ZEKİ İHTİYAROĞLU_874773_assignsubmission_file"
        to "AHMET_ZEKI_IHTIYAROGLU".

        Args:
            output_path: Directory containing folders to normalize

        Returns:
            Number of folders normalized
        """
        # Turkish character replacements
        turkish_replacements = {
            'Ç': 'C', 'ç': 'c',
            'Ğ': 'G', 'ğ': 'g',
            'İ': 'I', 'ı': 'i',
            'Ö': 'O', 'ö': 'o',
            'Ş': 'S', 'ş': 's',
            'Ü': 'U', 'ü': 'u',
        }

        normalized_count = 0

        for folder in output_path.iterdir():
            if not folder.is_dir():
                continue

            # Detect Moodle pattern: contains "_assignsubmission_file" or "_NNNNNN_"
            is_moodle_pattern = (
                '_assignsubmission_file' in folder.name or
                re.search(r'_\d{6,}_', folder.name)
            )

            if not is_moodle_pattern:
                continue

            # Extract name part (before first underscore followed by numbers)
            name_part = folder.name.split('_')[0]

            # Apply Turkish character replacements
            for orig, repl in turkish_replacements.items():
                name_part = name_part.replace(orig, repl)

            # Convert to ASCII, replace spaces with underscores, uppercase
            new_name = unidecode.unidecode(name_part).replace(' ', '_').upper()

            # Clean up any double underscores
            while '__' in new_name:
                new_name = new_name.replace('__', '_')

            new_path = output_path / new_name

            # Only rename if target doesn't exist and name changed
            if new_name != folder.name and not new_path.exists():
                folder.rename(new_path)
                normalized_count += 1

                if self.verbose:
                    print_info(f"Renamed: {folder.name} -> {new_name}")

        return normalized_count

    def cleanup(
        self,
        target_path: Optional[str | Path] = None,
        all_dirs: bool = False
    ) -> None:
        """Clean up generated result files.

        Args:
            target_path: Specific directory to clean (if not all_dirs)
            all_dirs: Recursively clean all subdirectories

        Raises:
            IOError: If cleanup fails
        """
        cleanup_service = CleanupService(verbose=self.verbose)

        if target_path is None:
            target_path = Path(".")
        else:
            target_path = Path(target_path)

        # Build list of temp directories to remove (inside target_path)
        temp_dirs_to_remove = []
        for dir_name in ['dolos-report', 'results']:
            dir_path = target_path / dir_name
            if dir_path.exists() and dir_path.is_dir():
                temp_dirs_to_remove.append(str(dir_path))

        if all_dirs:
            # Clean current directory and all subdirectories recursively
            subdirs = [d for d in target_path.rglob("*") if d.is_dir()]

            cleanup_service.cleanup_all(
                test_directories=[target_path] + subdirs,
                temp_directories=temp_dirs_to_remove,
            )
        else:
            # Clean specified directory or current directory
            cleanup_service.cleanup_all(
                target_path=target_path,
                temp_directories=temp_dirs_to_remove,
            )

    def cleanup_custom_dirs(
        self,
        target_dirs: list[Path],
        temp_dirs: Optional[list[str]] = None
    ) -> None:
        """Clean up custom list of directories.

        Args:
            target_dirs: List of directories to clean
            temp_dirs: Temporary directories to remove (optional)

        Raises:
            IOError: If cleanup fails
        """
        cleanup_service = CleanupService(verbose=self.verbose)

        if temp_dirs is None:
            temp_dirs = ['dolos-report']

        cleanup_service.cleanup_all(
            test_directories=target_dirs,
            temp_directories=temp_dirs,
        )

    def find_archives(
        self,
        target_path: Optional[str | Path] = None,
        exclude_pattern: Optional[str] = None,
    ) -> list[Path]:
        """Find all archive files in target directory recursively.

        Args:
            target_path: Directory to search (default: current directory)
            exclude_pattern: Glob pattern for files to exclude (e.g., '2025*Fall*CSE*')

        Returns:
            List of paths to archive files found
        """
        import fnmatch

        archive_extensions = [
            ".zip", ".rar", ".tar", ".tar.gz", ".tgz",
            ".tar.bz2", ".tar.xz", ".7z",
        ]

        if target_path is None:
            target_path = Path(".")
        else:
            target_path = Path(target_path)

        # Find all archive files
        archive_files = []
        for ext in archive_extensions:
            archive_files.extend(target_path.rglob(f"*{ext}"))

        # Always exclude results.zip (tool-generated) and venv directories
        archive_files = [
            f for f in archive_files
            if f.name != "results.zip"
            and ".venv" not in f.parts
            and "venv" not in f.parts
        ]

        # Apply user-defined exclude pattern
        if exclude_pattern:
            archive_files = [
                f for f in archive_files
                if not fnmatch.fnmatch(f.name, exclude_pattern)
            ]

        archive_files.sort()

        if archive_files:
            print_info(f"Found {len(archive_files)} archive file(s):")
            for archive_file in archive_files:
                print_info(f"  {archive_file}")
        else:
            print_info("No archive files found.")

        return archive_files
