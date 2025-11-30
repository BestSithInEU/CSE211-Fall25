"""Command-line interface for plagdet.

This module provides the main CLI entry point, integrating:
- Command-Handler separation for clean architecture
- Plugin auto-loading for detector/output/processor registration
- Rich traceback for better error messages
- Typer for modern CLI experience
"""

from pathlib import Path

import typer
from rich.traceback import install as install_rich_traceback

# Install rich traceback for better error messages
install_rich_traceback(show_locals=False)

from ..ui.console import console

# Import commands (thin CLI wrappers)
from .commands import (
    run_command,
    list_plugins_command,
    check_config_command,
    unzip_command,
    cleanup_command,
    find_archives_command,
    aggregate_command,
    report_command,
)

# Import plugins to register them (trigger decorators)
# This is intentional - importing plugins registers them via decorators
from ..plugins.detectors import copydetect_detector, dolos, jplag, moss
from ..plugins.outputs import csv, json
from ..plugins.processors import encoding_normalizer, normalizer, unzipper


# Create Typer app with rich help formatting
app = typer.Typer(
    name="plagdet",
    help="PlagDet - Multi-detector plagiarism detection tool with plugin architecture",
    add_completion=False,
    rich_markup_mode="rich",
    no_args_is_help=True,
)


# Register commands
# Using clear command names with underscores replaced by hyphens for CLI
app.command(name="run")(run_command)
app.command(name="list-plugins")(list_plugins_command)
app.command(name="check-config")(check_config_command)
app.command(name="unzip")(unzip_command)
app.command(name="cleanup")(cleanup_command)
app.command(name="find-archives")(find_archives_command)
app.command(name="aggregate")(aggregate_command)
app.command(name="report")(report_command)


# Version callback
def version_callback(value: bool):
    """Display version information."""
    if value:
        from .. import __version__
        console.print(f"plagdet version {__version__}")
        raise typer.Exit()


# Add version option
@app.callback()
def main(
    version: bool = typer.Option(
        False,
        "--version",
        "-v",
        callback=version_callback,
        is_eager=True,
        help="Show version and exit",
    )
):
    """PlagDet - Multi-detector plagiarism detection tool.

    A modern, plugin-based architecture for running multiple plagiarism
    detectors (JPlag, MOSS, Dolos, CopyDetect) with unified configuration
    and result aggregation.
    """
    pass


# Entry point for console_scripts in pyproject.toml
def cli_main():
    """Main entry point for CLI."""
    app()


if __name__ == "__main__":
    cli_main()
