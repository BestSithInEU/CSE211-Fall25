"""Utility commands - Unzip and cleanup operations."""

from pathlib import Path
from typing import List, Optional

import typer

from ...handlers.utility_handler import UtilityHandler
from ...ui.formatters import print_error


def unzip_command(
    zip_file: Path = typer.Argument(
        ...,
        exists=True,
        file_okay=True,
        dir_okay=False,
        readable=True,
        help="Path to ZIP archive file",
    ),
    output_dir: Path = typer.Argument(
        ...,
        help="Output directory for extracted files",
    ),
):
    """Unzip student submissions.

    Standalone utility to extract submission archives.

    [cyan]Example:[/cyan]
        plagdet unzip submissions.zip ./extracted/
    """
    try:
        handler = UtilityHandler()
        handler.unzip(zip_file, output_dir)

    except Exception as e:
        print_error(f"Failed to unzip: {e}")
        raise typer.Exit(code=1)


def cleanup_command(
    target_paths: Optional[List[Path]] = typer.Argument(
        None,
        help="Target directories to clean (default: current directory)",
    ),
    all_dirs: bool = typer.Option(
        False,
        "--all",
        "-a",
        help="Clean all subdirectories recursively",
    ),
):
    """Clean up generated result files.

    Removes CSV, JSON, ZIP files, results/ and dolos-report/ directories.

    [cyan]Examples:[/cyan]
        plagdet cleanup                              # Clean current directory
        plagdet cleanup ./lab1/ ./lab2/              # Clean multiple directories
        plagdet cleanup --all                        # Clean all subdirectories
    """
    try:
        handler = UtilityHandler()

        if target_paths:
            for target_path in target_paths:
                handler.cleanup(target_path=target_path, all_dirs=all_dirs)
        else:
            handler.cleanup(target_path=None, all_dirs=all_dirs)

    except Exception as e:
        print_error(f"Cleanup failed: {e}")
        raise typer.Exit(code=1)


def find_archives_command(
    target_path: Optional[Path] = typer.Argument(
        None,
        help="Target directory to search (default: current directory)",
    ),
):
    """Find all archive files (RAR, ZIP) recursively.

    Lists all archive files with their full paths.

    [cyan]Examples:[/cyan]
        plagdet find-archives                   # Search current directory
        plagdet find-archives ./submissions/    # Search specific directory
    """
    try:
        handler = UtilityHandler()
        handler.find_archives(target_path=target_path)

    except Exception as e:
        print_error(f"Find archives failed: {e}")
        raise typer.Exit(code=1)
