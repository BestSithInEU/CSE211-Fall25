"""Plugin registry system for managing and discovering plugins."""

from typing import Dict, Type

from rich.table import Table

from ..ui.console import console
from ..ui.themes import DEFAULT_THEME

# Global plugin registries
_detector_registry: Dict[str, Type] = {}
_output_registry: Dict[str, Type] = {}
_processor_registry: Dict[str, Type] = {}


def register_detector(cls):
    """Decorator to register a detector plugin.

    Args:
        cls: DetectorPlugin class to register

    Returns:
        The same class (for use as decorator)
    """
    instance = cls()
    _detector_registry[instance.name] = cls
    return cls


def register_output(cls):
    """Decorator to register an output plugin.

    Args:
        cls: OutputPlugin class to register

    Returns:
        The same class (for use as decorator)
    """
    instance = cls()
    _output_registry[instance.name] = cls
    return cls


def register_processor(cls):
    """Decorator to register a processor plugin.

    Args:
        cls: ProcessorPlugin class to register

    Returns:
        The same class (for use as decorator)
    """
    instance = cls()
    _processor_registry[instance.name] = cls
    return cls


def get_detector(name: str):
    """Get detector plugin class by name.

    Args:
        name: Plugin name from config

    Returns:
        DetectorPlugin class

    Raises:
        KeyError: If plugin not found
    """
    if name not in _detector_registry:
        available = list(_detector_registry.keys())
        raise KeyError(
            f"Detector '{name}' not found. Available detectors: {available}"
        )
    return _detector_registry[name]


def get_output(name: str):
    """Get output plugin class by name.

    Args:
        name: Plugin name from config

    Returns:
        OutputPlugin class

    Raises:
        KeyError: If plugin not found
    """
    if name not in _output_registry:
        available = list(_output_registry.keys())
        raise KeyError(
            f"Output plugin '{name}' not found. Available outputs: {available}"
        )
    return _output_registry[name]


def get_processor(name: str):
    """Get processor plugin class by name.

    Args:
        name: Plugin name from config

    Returns:
        ProcessorPlugin class

    Raises:
        KeyError: If plugin not found
    """
    if name not in _processor_registry:
        available = list(_processor_registry.keys())
        raise KeyError(
            f"Processor '{name}' not found. Available processors: {available}"
        )
    return _processor_registry[name]


def list_all_plugins():
    """List all registered plugins in a formatted table."""
    theme = DEFAULT_THEME

    # Create table for all plugins
    table = Table(
        title="Available Plugins",
        title_style=f"bold {theme.primary}",
        border_style=theme.border,
        header_style=theme.header,
        show_header=True,
        show_lines=False,
    )

    # Add columns
    table.add_column("Plugin Name", style=theme.accent, no_wrap=True)
    table.add_column("Type", style=theme.secondary)
    table.add_column("Status", style=theme.success)

    # Add detectors
    for name in sorted(_detector_registry.keys()):
        table.add_row(name, "Detector", "[✓] Available")

    # Add outputs
    for name in sorted(_output_registry.keys()):
        table.add_row(name, "Output", "[✓] Available")

    # Add processors
    for name in sorted(_processor_registry.keys()):
        table.add_row(name, "Processor", "[✓] Available")

    # Print the table
    console.print()
    console.print(table)
    console.print()

    # Print summary
    total = (
        len(_detector_registry)
        + len(_output_registry)
        + len(_processor_registry)
    )
    console.print(
        f"Total: {len(_detector_registry)} detectors, "
        f"{len(_output_registry)} outputs, "
        f"{len(_processor_registry)} processors "
        f"({total} plugins)",
        style=theme.muted,
    )
