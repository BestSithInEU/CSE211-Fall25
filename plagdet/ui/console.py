"""
Console manager for plagdet CLI.

Centralized Rich Console instance with theme support and configuration.
"""

import os
from typing import Optional

from rich.console import Console

from plagdet.ui.themes import DEFAULT_THEME, Theme, create_rich_theme

# Global console instance
_console: Optional[Console] = None
_current_theme: Theme = DEFAULT_THEME


def get_console(
    force_terminal: Optional[bool] = None,
    no_color: bool = False,
    theme: Optional[Theme] = None,
) -> Console:
    """Get or create the global console instance.

    Args:
        force_terminal: Force terminal mode (None = auto-detect)
        no_color: Disable all colors
        theme: Custom theme (None = use current theme)

    Returns:
        Rich Console instance
    """
    global _console, _current_theme

    # Update theme if provided
    if theme is not None:
        _current_theme = theme

    # Check NO_COLOR environment variable
    if no_color or os.environ.get("NO_COLOR"):
        no_color = True

    # Create console if not exists or settings changed
    if _console is None:
        _console = Console(
            theme=create_rich_theme(_current_theme),
            force_terminal=force_terminal,
            no_color=no_color,
            highlight=False,  # Disable automatic highlighting
        )

    return _console


def reset_console():
    """Reset the global console instance.

    Useful for testing or changing console configuration.
    """
    global _console
    _console = None


# Create default console instance
console = get_console()
