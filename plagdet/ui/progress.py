"""
Progress indicators for plagdet CLI.

Progress bars, spinners, and status tracking for long-running operations.
"""

from contextlib import contextmanager
from typing import Iterator, Optional

from rich.progress import (
    BarColumn,
    MofNCompleteColumn,
    Progress,
    SpinnerColumn,
    TaskID,
    TextColumn,
    TimeElapsedColumn,
    TimeRemainingColumn,
)

from plagdet.ui.console import get_console
from plagdet.ui.themes import DEFAULT_THEME, Theme


def create_progress(
    theme: Optional[Theme] = None,
    show_spinner: bool = True,
    show_time: bool = True,
) -> Progress:
    """Create a configured Progress instance.

    Args:
        theme: Optional theme override
        show_spinner: Show spinner for indeterminate tasks
        show_time: Show time elapsed and remaining

    Returns:
        Rich Progress instance
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    columns = []

    if show_spinner:
        columns.append(SpinnerColumn())

    columns.extend([
        TextColumn("[progress.description]{task.description}"),
        BarColumn(
            complete_style=theme.progress_complete,
            finished_style=theme.progress_complete,
            bar_width=40,
        ),
        MofNCompleteColumn(),
    ])

    if show_time:
        columns.extend([
            TimeElapsedColumn(),
            TimeRemainingColumn(),
        ])

    return Progress(*columns, console=console)


@contextmanager
def progress_bar(
    description: str,
    total: Optional[int] = None,
    theme: Optional[Theme] = None,
    show_spinner: bool = True,
    show_time: bool = True,
) -> Iterator[tuple[Progress, TaskID]]:
    """Context manager for progress bar.

    Args:
        description: Task description
        total: Total number of steps (None for indeterminate)
        theme: Optional theme override
        show_spinner: Show spinner
        show_time: Show time information

    Yields:
        Tuple of (Progress instance, TaskID)

    Example:
        with progress_bar("Processing files", total=100) as (progress, task):
            for i in range(100):
                process_file(i)
                progress.update(task, advance=1)
    """
    progress = create_progress(
        theme=theme,
        show_spinner=show_spinner,
        show_time=show_time,
    )

    with progress:
        task = progress.add_task(description, total=total)
        yield progress, task


@contextmanager
def spinner(
    description: str,
    theme: Optional[Theme] = None,
) -> Iterator[Progress]:
    """Context manager for spinner (indeterminate progress).

    Args:
        description: Task description
        theme: Optional theme override

    Yields:
        Progress instance

    Example:
        with spinner("Running JPlag..."):
            run_jplag()
    """
    theme = theme or DEFAULT_THEME
    console = get_console(theme=theme)

    progress = Progress(
        SpinnerColumn(),
        TextColumn("[progress.description]{task.description}"),
        console=console,
    )

    with progress:
        progress.add_task(description, total=None)
        yield progress
