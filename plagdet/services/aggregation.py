"""Aggregation service for combining multi-detector results.

This service extracts the aggregation logic that was previously duplicated
in both engine.py and cli.py (220+ lines).
"""

import csv
from collections import defaultdict
from pathlib import Path
from typing import Dict, List, Optional, Tuple

from ..core.models.detection import DetectionResult
from ..ui.formatters import print_info, print_success, print_warning


class AggregationService:
    """Service for aggregating results from multiple plagiarism detectors.

    Combines similarity scores from different detectors into a unified view,
    generating CSV output with individual detector scores plus aggregated metrics.
    """

    def __init__(self, verbose: bool = False):
        """Initialize aggregation service.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def aggregate_results(
        self,
        results: List[Tuple[str, DetectionResult]],
        output_path: Path,
        min_score: float = 0.0,
    ) -> bool:
        """Aggregate results from multiple detectors into a single CSV.

        Args:
            results: List of (detector_name, DetectionResult) tuples
            output_path: Path to write aggregated CSV file
            min_score: Minimum average score to include (0-100)

        Returns:
            True if aggregation succeeded, False otherwise
        """
        if not results:
            if self.verbose:
                print_warning("No results to aggregate")
            return False

        if len(results) < 2:
            if self.verbose:
                print_info("Only one detector result, skipping aggregation")
            return False

        try:
            if self.verbose:
                print_info(f"Aggregating results from {len(results)} detectors")

            # Aggregate by student pair
            aggregated = self._aggregate_by_pair(results)

            # Prepare output rows
            output_rows = self._prepare_output_rows(
                aggregated, results, min_score
            )

            if not output_rows:
                if self.verbose:
                    print_warning(
                        f"No pairs met minimum score threshold of {min_score}%"
                    )
                return False

            # Write CSV
            self._write_csv(output_path, output_rows, results)

            detector_names = [name for name, _ in results]
            print_success(
                f"Aggregated {len(output_rows)} pairs to {output_path}"
            )
            if self.verbose:
                print_info(f"Detectors included: {', '.join(detector_names)}")

            return True

        except Exception as e:
            print_warning(f"Aggregation failed: {e}")
            if self.verbose:
                import traceback
                traceback.print_exc()
            return False

    def _aggregate_by_pair(
        self, results: List[Tuple[str, DetectionResult]]
    ) -> Dict[Tuple[str, str], Dict]:
        """Aggregate comparisons by student pair.

        Args:
            results: List of (detector_name, DetectionResult) tuples

        Returns:
            Dictionary mapping pair keys to aggregated data
        """
        aggregated = defaultdict(lambda: {'detectors': {}})

        for detector_name, result in results:
            for comp in result.comparisons:
                first = comp.first_submission
                second = comp.second_submission
                # Convert similarity to percentage (0-100)
                similarity = comp.similarity * 100.0

                # Create unique key for this pair (order-independent)
                pair_key = tuple(sorted([first, second]))

                # Store first/second using original order
                if 'first' not in aggregated[pair_key]:
                    aggregated[pair_key]['first'] = first
                    aggregated[pair_key]['second'] = second

                # Store detector similarity
                aggregated[pair_key]['detectors'][detector_name] = similarity

        return aggregated

    def _prepare_output_rows(
        self,
        aggregated: Dict[Tuple[str, str], Dict],
        results: List[Tuple[str, DetectionResult]],
        min_score: float,
    ) -> List[Dict[str, str]]:
        """Prepare output rows from aggregated data.

        Args:
            aggregated: Aggregated data by pair
            results: Original detector results
            min_score: Minimum average score threshold

        Returns:
            List of row dictionaries for CSV output
        """
        output_rows = []
        all_detectors = [name for name, _ in results]

        for pair_key, data in aggregated.items():
            scores = []
            row = {
                'First Submission': data['first'],
                'Second Submission': data['second'],
            }

            # Add each detector's score
            for detector_name in all_detectors:
                score = data['detectors'].get(detector_name, None)
                if score is not None:
                    row[detector_name.upper()] = f"{score:.2f}"
                    scores.append(score)
                else:
                    row[detector_name.upper()] = '-'

            # Calculate average and count
            if scores:
                avg_score = sum(scores) / len(scores)
                row['Average'] = f"{avg_score:.2f}"
                row['Count'] = str(len(scores))

                # Apply min_score filter to average
                if avg_score >= min_score:
                    output_rows.append(row)

        # Sort by average score (descending)
        output_rows.sort(
            key=lambda x: float(x.get('Average', 0)), reverse=True
        )

        return output_rows

    def _write_csv(
        self,
        output_path: Path,
        output_rows: List[Dict[str, str]],
        results: List[Tuple[str, DetectionResult]],
    ) -> None:
        """Write aggregated data to CSV file.

        Args:
            output_path: Path to output CSV file
            output_rows: List of row dictionaries
            results: Original detector results (for field names)
        """
        all_detectors = [name for name, _ in results]
        fieldnames = (
            ['First Submission', 'Second Submission']
            + [d.upper() for d in all_detectors]
            + ['Average', 'Count']
        )

        with open(output_path, 'w', newline='', encoding='utf-8') as csvfile:
            writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(output_rows)

    def aggregate_from_json_files(
        self,
        target_path: Path,
        output_path: Optional[Path] = None,
        min_score: float = 0.0,
    ) -> bool:
        """Aggregate results from JSON files in a directory.

        This method reads detector JSON output files and aggregates them.
        Used by the CLI aggregate command.

        Args:
            target_path: Directory containing detector JSON files
            output_path: Output CSV path (default: target_path/aggregated.csv)
            min_score: Minimum average score to include (0-100)

        Returns:
            True if aggregation succeeded, False otherwise
        """
        import json

        # Determine output path
        if output_path is None:
            output_path = target_path / 'aggregated.csv'

        # Find all detector JSON files
        json_files = list(target_path.glob('*_*.json'))

        if not json_files:
            print_warning(f"No detector JSON files found in {target_path}")
            print_info("Expected files like: lab1_jplag.json, lab1_moss.json, etc.")
            return False

        if self.verbose:
            print_info(f"Found {len(json_files)} detector result file(s)")

        # Read all JSON files and organize by detector
        detector_results = {}
        for json_file in json_files:
            try:
                # Extract detector name from filename (e.g., lab1_jplag.json -> jplag)
                filename = json_file.name
                parts = filename.replace('.json', '').split('_')
                detector_name = parts[-1] if len(parts) > 1 else 'unknown'

                with open(json_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    comparisons_data = data.get('comparisons', [])

                # Convert dict comparisons to Comparison objects
                from ..core.models.detection import Comparison
                comparisons = []
                for comp_dict in comparisons_data:
                    try:
                        # Handle similarity as both 0-1 and 0-100 ranges
                        sim = comp_dict.get('similarity', 0.0)
                        if sim > 1.0:  # Already in percentage
                            sim = sim / 100.0

                        comp = Comparison(
                            first_submission=comp_dict.get('first_submission', ''),
                            second_submission=comp_dict.get('second_submission', ''),
                            similarity=sim,
                            metric=comp_dict.get('metric', 'UNKNOWN'),
                        )
                        comparisons.append(comp)
                    except Exception as e:
                        if self.verbose:
                            print_warning(f"Skipping invalid comparison: {e}")
                        continue

                result = DetectionResult(comparisons=comparisons, metadata=data.get('metadata', {}))
                detector_results[detector_name] = result

                if self.verbose:
                    print_info(f"  - {detector_name}: {len(comparisons)} comparisons")

            except Exception as e:
                print_warning(f"Failed to read {json_file}: {e}")
                continue

        if not detector_results:
            print_warning("No valid detector results found")
            return False

        # Convert to list of tuples
        results = list(detector_results.items())

        # Use standard aggregation method
        return self.aggregate_results(results, output_path, min_score)
