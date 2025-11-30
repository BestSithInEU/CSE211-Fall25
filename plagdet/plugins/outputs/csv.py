"""CSV output plugin for plagiarism detection results."""

import csv
from pathlib import Path
from typing import Set

from pydantic import BaseModel

from ...core.models.detection import DetectionResult
from ..base import OutputPlugin
from ..models.outputs import CSVOutputConfig
from ...core.registry import register_output


@register_output
class CSVOutput(OutputPlugin):
    """CSV output formatter for detection results."""

    # Specify expected config type for validation
    CONFIG_TYPE = CSVOutputConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "csv"

    def write(
        self,
        result: DetectionResult,
        output_path: str | Path,
        config: BaseModel
    ) -> None:
        """Write detection results to CSV file.

        Args:
            result: Detection results (Pydantic model) to write
            output_path: Path to output CSV file
            config: CSVOutputConfig with formatting options
        """
        # Type-safe config access
        csv_config = config if isinstance(config, CSVOutputConfig) else CSVOutputConfig(**config.model_dump())

        min_score = csv_config.min_score
        metric = csv_config.metric
        include_unique_names = csv_config.include_unique_names

        unique_names: Set[str] = set()

        # Convert min_score from percentage to decimal
        min_score_decimal = min_score / 100.0

        # Filter and sort results using Pydantic model methods
        filtered_result = result.filter_by_threshold(min_score_decimal).sort_by_similarity()

        output_path_str = str(output_path)

        # Write main results CSV
        with open(output_path_str, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.writer(csvfile)
            writer.writerow(['First Submission', 'Second Submission', 'Similarity'])

            for comparison in filtered_result.comparisons:
                # Filter by metric if available
                comparison_metric = comparison.metric.upper()
                if comparison_metric != metric:
                    continue

                # Get similarity as percentage
                similarity = comparison.get_similarity_percentage()

                first = comparison.first_submission
                second = comparison.second_submission

                writer.writerow([first, second, f"{similarity:.2f}"])

                # Collect unique names
                if include_unique_names:
                    unique_names.add(first)
                    unique_names.add(second)

        # Write unique names if requested
        if include_unique_names and unique_names:
            self._write_unique_names(output_path_str, unique_names)

    def _write_unique_names(self, output_path: str, unique_names: Set[str]) -> None:
        """Write unique student names to a separate CSV file.

        Args:
            output_path: Base output path
            unique_names: Set of unique student names
        """
        output_dir = Path(output_path).parent
        unique_path = output_dir / "unique_names.csv"

        with open(unique_path, 'w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(['Name'])
            for name in sorted(unique_names):
                writer.writerow([name])
