"""Handler for configuration validation and display."""

from pathlib import Path

from pydantic import ValidationError
from rich.table import Table
from rich.panel import Panel

from ..core.config import AppConfig
from ..ui.console import console
from ..ui.formatters import print_error, print_info, print_success


class ConfigHandler:
    """Handler for configuration file operations.

    Validates configuration files and displays structured summaries.
    """

    def validate_and_display(self, config_path: str | Path) -> None:
        """Validate config file and display comprehensive summary.

        Args:
            config_path: Path to YAML configuration file

        Raises:
            ValidationError: If configuration is invalid
            FileNotFoundError: If config file doesn't exist
        """
        try:
            # Load and validate
            print_info(f"Validating configuration: {config_path}")
            app_config = AppConfig.load_from_yaml(str(config_path))

            # Display success message
            console.print()
            console.print(Panel(
                "[bold green]✓ Configuration is valid![/bold green]",
                border_style="green"
            ))
            console.print()

            # Display all sections
            self._display_detectors(app_config)
            self._display_outputs(app_config)
            self._display_processors(app_config)
            self._display_settings(app_config)

            print_success(f"Configuration file '{config_path}' is valid and ready to use!")

        except ValidationError as e:
            self._display_validation_errors(e)
            raise

        except FileNotFoundError:
            print_error(f"Configuration file not found: {config_path}")
            raise

        except Exception as e:
            print_error(f"Failed to load configuration: {e}")
            console.print_exception(show_locals=False)
            raise

    def _display_detectors(self, config: AppConfig) -> None:
        """Display configured detectors in a table.

        Args:
            config: Application configuration
        """
        table = Table(title="Configured Detectors", border_style="cyan")
        table.add_column("Detector", style="cyan")
        table.add_column("Language", style="yellow")
        table.add_column("Config Options", style="dim")

        for detector in config.detectors:
            language = detector.config.get('language', 'N/A')
            config_keys = ', '.join(detector.config.keys()) if detector.config else 'None'
            table.add_row(detector.name, str(language), config_keys)

        console.print(table)
        console.print()

    def _display_outputs(self, config: AppConfig) -> None:
        """Display configured outputs in a table.

        Args:
            config: Application configuration
        """
        table = Table(title="Configured Outputs", border_style="cyan")
        table.add_column("Output", style="cyan")
        table.add_column("Config Options", style="dim")

        for output in config.outputs:
            config_keys = ', '.join(output.config.keys()) if output.config else 'None'
            table.add_row(output.name, config_keys)

        console.print(table)
        console.print()

    def _display_processors(self, config: AppConfig) -> None:
        """Display configured processors.

        Args:
            config: Application configuration
        """
        console.print("[bold cyan]Processors:[/bold cyan]")
        console.print(f"  Pre-detection:  {len(config.processors.pre_detection)} processor(s)")
        for proc in config.processors.pre_detection:
            console.print(f"    - {proc.name}")
        console.print(f"  Post-detection: {len(config.processors.post_detection)} processor(s)")
        for proc in config.processors.post_detection:
            console.print(f"    - {proc.name}")
        console.print()

    def _display_settings(self, config: AppConfig) -> None:
        """Display settings in a table.

        Args:
            config: Application configuration
        """
        table = Table(title="Settings", border_style="cyan")
        table.add_column("Setting", style="cyan")
        table.add_column("Value", style="yellow")

        table.add_row("Target Path", config.settings.target_path)
        table.add_row("Cleanup Temp", str(config.settings.cleanup_temp))
        table.add_row("Verbose", str(config.settings.verbose))

        console.print(table)
        console.print()

    def _display_validation_errors(self, error: ValidationError) -> None:
        """Display Pydantic validation errors in a formatted way.

        Args:
            error: Pydantic ValidationError
        """
        console.print()
        console.print(Panel(
            "[bold red]✗ Configuration validation failed![/bold red]",
            border_style="red"
        ))
        console.print()
        print_error("Pydantic validation errors:")
        console.print()

        for err in error.errors():
            location = " → ".join(str(loc) for loc in err['loc'])
            console.print(f"  [red]✗[/red] [bold]{location}[/bold]")
            console.print(f"    {err['msg']}")
            console.print(f"    [dim]Type: {err['type']}[/dim]")
            console.print()
