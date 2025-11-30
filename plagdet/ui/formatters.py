"""
Output formatters for plagdet CLI.

Rich-based message formatting functions to replace legacy utils.py.
"""

from typing import Optional

from rich.panel import Panel
from rich.text import Text

from plagdet.ui.console import get_console
from plagdet.ui.themes import DEFAULT_THEME, Theme


def print_success(
    message: str,
    title: Optional[str] = None,
    theme: Optional[Theme] = None,
):
    """Print a success message.

    Args:
        message: Success message to display
        title: Optional panel title
        theme: Optional theme override
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    text = Text()
    text.append(f"{theme.symbol_success} ", style=theme.success)
    text.append(message)

    if title:
        panel = Panel(
            text,
            title=title,
            border_style=theme.success,
            expand=False,
        )
        console.print(panel)
    else:
        console.print(text)


def print_error(
    message: str,
    title: Optional[str] = None,
    theme: Optional[Theme] = None,
):
    """Print an error message.

    Args:
        message: Error message to display
        title: Optional panel title
        theme: Optional theme override
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    text = Text()
    text.append(f"{theme.symbol_error} ", style=theme.error)
    text.append(message)

    if title:
        panel = Panel(
            text,
            title=title,
            border_style=theme.error,
            expand=False,
        )
        console.print(panel)
    else:
        console.print(text)


def print_warning(
    message: str,
    title: Optional[str] = None,
    theme: Optional[Theme] = None,
):
    """Print a warning message.

    Args:
        message: Warning message to display
        title: Optional panel title
        theme: Optional theme override
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    text = Text()
    text.append(f"{theme.symbol_warning} ", style=theme.warning)
    text.append(message)

    if title:
        panel = Panel(
            text,
            title=title,
            border_style=theme.warning,
            expand=False,
        )
        console.print(panel)
    else:
        console.print(text)


def print_info(
    message: str,
    title: Optional[str] = None,
    theme: Optional[Theme] = None,
):
    """Print an info message.

    Args:
        message: Info message to display
        title: Optional panel title
        theme: Optional theme override
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    text = Text()
    text.append(f"{theme.symbol_info} ", style=theme.info)
    text.append(message)

    if title:
        panel = Panel(
            text,
            title=title,
            border_style=theme.info,
            expand=False,
        )
        console.print(panel)
    else:
        console.print(text)


def print_running(
    message: str,
    title: Optional[str] = None,
    theme: Optional[Theme] = None,
):
    """Print a running/in-progress message.

    Args:
        message: Running message to display
        title: Optional panel title
        theme: Optional theme override
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    text = Text()
    text.append(f"{theme.symbol_running} ", style=theme.primary)
    text.append(message)

    if title:
        panel = Panel(
            text,
            title=title,
            border_style=theme.primary,
            expand=False,
        )
        console.print(panel)
    else:
        console.print(text)
