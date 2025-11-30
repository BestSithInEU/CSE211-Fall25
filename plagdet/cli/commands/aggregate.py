"""Aggregate command - Combine multi-detector results."""

from pathlib import Path
from typing import Optional

import typer

from ...handlers.aggregate_handler import AggregateHandler
from ...ui.formatters import print_error


def aggregate_command(
    target_path: Path = typer.Argument(
        ...,
        exists=True,
        file_okay=False,
        dir_okay=True,
        readable=True,
        help="Target directory containing detector JSON files",
    ),
    output: Optional[Path] = typer.Option(
        None,
        "--output",
        "-o",
        help="Output CSV file path (default: <target_path>/aggregated.csv)",
    ),
    min_score: float = typer.Option(
        0.0,
        "--min-score",
        "-m",
        min=0.0,
        max=100.0,
        help="Minimum similarity score to include (0-100)",
    ),
):
    """Aggregate results from multiple detectors into a single CSV.

    Reads JSON result files from all detectors and combines them into a single
    CSV showing each detector's score plus average.

    [cyan]Examples:[/cyan]
        plagdet aggregate ./results/
        plagdet aggregate ./output/ --output combined.csv
        plagdet aggregate ./data/ --min-score 70
    """
    try:
        handler = AggregateHandler(verbose=True)
        success = handler.aggregate(
            target_path=target_path,
            output_path=output,
            min_score=min_score
        )

        if not success:
            raise typer.Exit(code=1)

    except typer.Exit:
        raise
    except Exception as e:
        print_error(f"Aggregation failed: {e}")
        raise typer.Exit(code=1)
