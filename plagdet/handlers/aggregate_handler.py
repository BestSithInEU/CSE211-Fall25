"""Handler for result aggregation operations."""

from pathlib import Path
from typing import Optional

from ..services.aggregation import AggregationService
from ..ui.console import console
from ..ui.formatters import print_error


class AggregateHandler:
    """Handler for aggregating multi-detector results.

    Combines results from multiple detectors into a single CSV.
    """

    def __init__(self, verbose: bool = True):
        """Initialize handler.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def aggregate(
        self,
        target_path: str | Path,
        output_path: Optional[str | Path] = None,
        min_score: float = 0.0
    ) -> bool:
        """Aggregate detector results into single CSV.

        Args:
            target_path: Directory containing detector JSON files
            output_path: Output CSV file path (default: <target_path>/aggregated.csv)
            min_score: Minimum similarity score to include (0-100)

        Returns:
            True if aggregation succeeded, False otherwise

        Raises:
            FileNotFoundError: If target_path doesn't exist
            IOError: If aggregation fails
        """
        target = Path(target_path)

        # Validate target directory exists
        if not target.exists():
            raise FileNotFoundError(f"Target directory not found: {target_path}")

        if not target.is_dir():
            raise ValueError(f"Target path is not a directory: {target_path}")

        # Use aggregation service
        aggregation_service = AggregationService(verbose=self.verbose)

        try:
            success = aggregation_service.aggregate_from_json_files(
                target_path=target,
                output_path=Path(output_path) if output_path else None,
                min_score=min_score,
            )

            return success

        except Exception as e:
            print_error(f"Aggregation failed: {e}")
            if self.verbose:
                console.print_exception(show_locals=False)
            return False

    def aggregate_results(
        self,
        json_files: list[Path],
        output_path: Path,
        min_score: float = 0.0
    ) -> bool:
        """Aggregate specific JSON result files.

        Args:
            json_files: List of JSON result file paths
            output_path: Output CSV file path
            min_score: Minimum similarity score to include (0-100)

        Returns:
            True if aggregation succeeded, False otherwise
        """
        aggregation_service = AggregationService(verbose=self.verbose)

        try:
            # This would need a new method in AggregationService
            # For now, delegate to the main aggregate method
            # by passing the directory containing the files
            if json_files:
                parent_dir = json_files[0].parent
                return aggregation_service.aggregate_from_json_files(
                    target_path=parent_dir,
                    output_path=output_path,
                    min_score=min_score,
                )
            return False

        except Exception as e:
            print_error(f"Aggregation failed: {e}")
            return False
