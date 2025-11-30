"""
Theme definitions for jplag-runner CLI.

Professional color schemes and styling without emoji dependencies.
"""

from dataclasses import dataclass
from typing import Dict

from rich.style import Style
from rich.theme import Theme as RichTheme


@dataclass
class Theme:
    """Theme configuration for CLI output."""

    # Status colors
    success: str = "green"
    error: str = "red"
    warning: str = "yellow"
    info: str = "cyan"

    # UI elements
    primary: str = "blue"
    secondary: str = "magenta"
    accent: str = "bright_cyan"
    muted: str = "bright_black"

    # Table colors
    header: str = "bold cyan"
    border: str = "blue"
    row_alt: str = "bright_black"

    # Progress
    progress_bar: str = "cyan"
    progress_complete: str = "green"

    # Syntax
    keyword: str = "magenta"
    string: str = "green"
    number: str = "cyan"

    # Status symbols (no emojis, Unicode box-drawing)
    symbol_success: str = "[✓]"
    symbol_error: str = "[✗]"
    symbol_warning: str = "[!]"
    symbol_info: str = "[i]"
    symbol_running: str = "[→]"


# Default theme
DEFAULT_THEME = Theme()

# Alternative theme configurations
THEMES: Dict[str, Theme] = {
    "default": DEFAULT_THEME,
    "minimal": Theme(
        success="white",
        error="white",
        warning="white",
        info="white",
        primary="white",
        secondary="white",
        accent="white",
        muted="bright_black",
        header="bold",
        border="white",
        row_alt="bright_black",
        progress_bar="white",
        progress_complete="white",
        keyword="white",
        string="white",
        number="white",
    ),
    "high-contrast": Theme(
        success="bright_green",
        error="bright_red",
        warning="bright_yellow",
        info="bright_cyan",
        primary="bright_blue",
        secondary="bright_magenta",
        accent="bright_white",
        muted="white",
        header="bold bright_cyan",
        border="bright_blue",
        row_alt="white",
        progress_bar="bright_cyan",
        progress_complete="bright_green",
        keyword="bright_magenta",
        string="bright_green",
        number="bright_cyan",
    ),
}


def get_theme(name: str = "default") -> Theme:
    """Get a theme by name.

    Args:
        name: Theme name (default, minimal, high-contrast)

    Returns:
        Theme instance

    Raises:
        KeyError: If theme name is not found
    """
    if name not in THEMES:
        available = ", ".join(THEMES.keys())
        raise KeyError(f"Theme '{name}' not found. Available themes: {available}")
    return THEMES[name]


def create_rich_theme(theme: Theme) -> RichTheme:
    """Convert Theme to Rich theme for console styling.

    Args:
        theme: Theme instance

    Returns:
        Rich Theme instance
    """
    return RichTheme({
        "success": Style(color=theme.success),
        "error": Style(color=theme.error),
        "warning": Style(color=theme.warning),
        "info": Style(color=theme.info),
        "primary": Style(color=theme.primary),
        "secondary": Style(color=theme.secondary),
        "accent": Style(color=theme.accent),
        "muted": Style(color=theme.muted),
        "header": Style.parse(theme.header),
        "border": Style(color=theme.border),
        "progress.bar": Style(color=theme.progress_bar),
        "progress.complete": Style(color=theme.progress_complete),
    })
