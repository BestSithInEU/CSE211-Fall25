"""Run command - Execute plagiarism detection."""

from pathlib import Path
from typing import List, Optional

import typer

from ...handlers.run_handler import RunHandler
from ...ui.formatters import print_error


def run_command(
    config: Path = typer.Option(
        ...,
        "--config",
        "-c",
        exists=True,
        file_okay=True,
        dir_okay=False,
        readable=True,
        help="Path to YAML configuration file",
    ),
    verbose: bool = typer.Option(
        False,
        "--verbose",
        "-v",
        help="Enable verbose output with detailed logging",
    ),
    detectors: Optional[List[str]] = typer.Option(
        None,
        "--detector",
        "-d",
        help="Override config: run specific detector(s). Can specify multiple times.",
    ),
    all_detectors: bool = typer.Option(
        False,
        "--all-detectors",
        help="Override config: run ALL available detectors",
    ),
):
    """Run plagiarism detection with a configuration file.

    [cyan]Examples:[/cyan]
        # Use detectors from config
        plagdet run -c config.yaml

        # Override: run only JPlag
        plagdet run -c config.yaml -d jplag

        # Override: run JPlag and MOSS
        plagdet run -c config.yaml -d jplag -d moss

        # Override: run ALL detectors
        plagdet run -c config.yaml --all-detectors
    """
    try:
        handler = RunHandler(verbose=verbose)
        handler.execute(
            config_path=config,
            detector_override=detectors,
            all_detectors=all_detectors
        )

    except Exception as e:
        print_error(f"Command failed: {e}")
        raise typer.Exit(code=1)
