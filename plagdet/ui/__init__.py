"""
UI module for plagdet CLI.

Provides Rich-based terminal UI components including console management,
themes, formatters, and progress indicators.
"""

from plagdet.ui.console import console, get_console
from plagdet.ui.formatters import (
    print_error,
    print_info,
    print_success,
    print_warning,
)
from plagdet.ui.themes import Theme, get_theme

__all__ = [
    "console",
    "get_console",
    "print_error",
    "print_info",
    "print_success",
    "print_warning",
    "Theme",
    "get_theme",
]
