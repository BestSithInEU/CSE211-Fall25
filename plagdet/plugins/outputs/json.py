"""JSON output plugin for plagiarism detection results."""

import json
from pathlib import Path

from pydantic import BaseModel

from ...core.models.detection import DetectionResult
from ..base import OutputPlugin
from ..models.outputs import JSONOutputConfig
from ...core.registry import register_output


@register_output
class JSONOutput(OutputPlugin):
    """JSON output formatter for detection results."""

    # Specify expected config type for validation
    CONFIG_TYPE = JSONOutputConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "json"

    def write(
        self,
        result: DetectionResult,
        output_path: str | Path,
        config: BaseModel
    ) -> None:
        """Write detection results to JSON file.

        Args:
            result: Detection results (Pydantic model) to write
            output_path: Path to output JSON file
            config: JSONOutputConfig with formatting options
        """
        # Type-safe config access
        json_config = config if isinstance(config, JSONOutputConfig) else JSONOutputConfig(**config.model_dump())

        pretty = json_config.pretty
        indent = json_config.indent if pretty else None
        include_metadata = json_config.include_metadata
        min_score = json_config.min_score

        # Convert min_score from percentage to decimal for filtering
        min_score_decimal = min_score / 100.0

        # Filter comparisons using Pydantic model method
        filtered_result = result.filter_by_threshold(min_score_decimal)

        # Build output structure using Pydantic's to_dict method
        output_data = filtered_result.to_dict()

        if not include_metadata:
            output_data.pop('metadata', None)

        # Write to file
        with open(str(output_path), 'w', encoding='utf-8') as f:
            json.dump(output_data, f, indent=indent, ensure_ascii=False)
