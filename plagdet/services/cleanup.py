"""Cleanup service for removing generated result files.

This service extracts cleanup logic from cli.py.
"""

import shutil
from pathlib import Path
from typing import List

from ..ui.console import console
from ..ui.formatters import print_error, print_success


class CleanupService:
    """Service for cleaning up generated result files."""

    def __init__(self, verbose: bool = False):
        """Initialize cleanup service.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def cleanup_directory(
        self,
        target_path: Path,
        patterns: List[str] = None,
    ) -> List[str]:
        """Clean result files from a directory.

        Args:
            target_path: Path to directory to clean
            patterns: File patterns to remove (default: ['*.csv', '*.json'])

        Returns:
            List of removed file paths
        """
        if patterns is None:
            patterns = ['*.csv', '*.json', 'result*.zip']

        removed = []

        if not target_path.exists():
            return removed

        for pattern in patterns:
            for file in target_path.glob(pattern):
                try:
                    file.unlink()
                    removed.append(str(file))
                except Exception as e:
                    if self.verbose:
                        print_error(f"Failed to remove {file}: {e}")

        return removed

    def cleanup_directories(
        self,
        directories: List[Path],
        patterns: List[str] = None,
    ) -> List[str]:
        """Clean result files from multiple directories.

        Args:
            directories: List of directories to clean
            patterns: File patterns to remove

        Returns:
            Combined list of removed file paths
        """
        all_removed = []

        for directory in directories:
            removed = self.cleanup_directory(directory, patterns)
            all_removed.extend(removed)

        return all_removed

    def cleanup_temp_directories(
        self,
        directories: List[str] = None,
    ) -> List[str]:
        """Clean up temporary directories (like dolos-report, results).

        Args:
            directories: List of directory paths to remove (full paths or relative)

        Returns:
            List of removed directory paths
        """
        if directories is None:
            return []

        removed = []

        for dir_path_str in directories:
            dir_path = Path(dir_path_str)
            if dir_path.exists() and dir_path.is_dir():
                try:
                    shutil.rmtree(dir_path)
                    removed.append(str(dir_path) + '/')
                except Exception as e:
                    if self.verbose:
                        print_error(f"Failed to remove {dir_path}: {e}")

        return removed

    def cleanup_all(
        self,
        target_path: Path = None,
        test_directories: List[Path] = None,
        file_patterns: List[str] = None,
        temp_directories: List[str] = None,
    ) -> bool:
        """Comprehensive cleanup of all generated files.

        Args:
            target_path: Specific directory to clean
            test_directories: List of test directories to clean
            file_patterns: File patterns to remove
            temp_directories: Temporary directories to remove

        Returns:
            True if any files were cleaned, False otherwise
        """
        all_cleaned = []

        # Clean specific directory if provided
        if target_path and target_path.exists():
            removed = self.cleanup_directory(target_path, file_patterns)
            all_cleaned.extend(removed)

        # Clean test directories if provided
        if test_directories:
            for test_dir in test_directories:
                if test_dir.exists():
                    removed = self.cleanup_directory(test_dir, file_patterns)
                    all_cleaned.extend(removed)

        # Clean temporary directories
        removed_dirs = self.cleanup_temp_directories(temp_directories)
        all_cleaned.extend(removed_dirs)

        # Report results
        if all_cleaned:
            print_success("Cleaned up old results:")
            for item in all_cleaned:
                console.print(f"  - {item}")
            return True
        else:
            console.print("No files to clean")
            return False
