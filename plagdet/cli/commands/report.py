"""Report command for generating human-readable plagiarism reports."""

from pathlib import Path
from typing import Optional

import typer

from ...handlers.report_handler import ReportHandler


def report_command(
    path: Optional[str] = typer.Argument(
        None,
        help="Path to JPlag CSV or results directory"
    ),
    all_projects: bool = typer.Option(
        False, "--all", "-a",
        help="Generate reports for all results directories"
    ),
    output: Optional[str] = typer.Option(
        None, "-o", "--output",
        help="Output file path for HTML report"
    ),
    threshold: float = typer.Option(
        50.0, "-t", "--threshold",
        help="Minimum similarity threshold for flagging (default: 50%)"
    ),
    html: bool = typer.Option(
        False, "--html",
        help="Generate HTML report instead of console output"
    ),
    verbose: bool = typer.Option(
        False, "-v", "--verbose",
        help="Enable verbose output"
    )
) -> None:
    """Generate a human-readable plagiarism detection report.

    Takes JPlag results and produces a student-centric report
    with risk levels and flagged pairs.

    Examples:
        # Console report for single project
        plagdet report section1/labwork1-Even/results/

        # HTML report for single project
        plagdet report section1/labwork1-Even/results/ --html

        # HTML reports for ALL projects
        plagdet report --all --html

        # Custom threshold
        plagdet report section1/labwork1-Even/results/ -t 60
    """
    handler = ReportHandler(verbose=verbose)
    format_type = "html" if html else "console"

    try:
        if all_projects:
            # Generate reports for all results directories
            handler.generate_all(
                threshold=threshold,
                format=format_type
            )
        else:
            if not path:
                typer.echo("Error: path is required unless --all is used", err=True)
                raise typer.Exit(1)

            if html and not output:
                # Default HTML output path
                results_path = Path(path)
                if results_path.is_dir():
                    output = str(results_path / "plagiarism_report.html")
                else:
                    output = str(results_path.parent / "plagiarism_report.html")

            handler.generate(
                results_path=path,
                output_path=output,
                threshold=threshold,
                format=format_type
            )
    except FileNotFoundError as e:
        typer.echo(f"Error: {e}", err=True)
        raise typer.Exit(1)
    except Exception as e:
        typer.echo(f"Error generating report: {e}", err=True)
        if verbose:
            import traceback
            traceback.print_exc()
        raise typer.Exit(1)
