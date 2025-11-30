"""Config command - Validate configuration files."""

from pathlib import Path

import typer

from ...handlers.config_handler import ConfigHandler


def check_config_command(
    config: Path = typer.Argument(
        ...,
        exists=True,
        file_okay=True,
        dir_okay=False,
        readable=True,
        help="Path to YAML configuration file to validate",
    ),
):
    """Validate configuration file syntax and show summary.

    Checks YAML syntax, Pydantic model validation, and displays
    a summary of configured detectors, outputs, and settings.

    [cyan]Examples:[/cyan]
        plagdet check-config config.yaml
        plagdet check-config my-custom-config.yaml
    """
    try:
        handler = ConfigHandler()
        handler.validate_and_display(config)

    except Exception:
        # Handler already displays errors
        raise typer.Exit(code=1)
