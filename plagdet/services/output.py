"""Output manager service for generating detector outputs.

This service extracts output generation logic from engine.py.
"""

from pathlib import Path
from typing import Dict, List

from ..core.exceptions import OutputError, PluginError
from ..core.models.config import OutputConfig
from ..core.models.detection import DetectionResult
from ..core.registry import get_output
from ..plugins.models.outputs import CSVOutputConfig, JSONOutputConfig
from ..ui.formatters import print_info, print_success


class OutputManager:
    """Service for managing output generation from detection results."""

    # Map output names to their Pydantic config classes
    OUTPUT_CONFIG_MAP = {
        'csv': CSVOutputConfig,
        'json': JSONOutputConfig,
    }

    def __init__(self, verbose: bool = False):
        """Initialize output manager.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def generate_outputs(
        self,
        detector_name: str,
        result: DetectionResult,
        output_configs: List[OutputConfig],
        target_path: Path,
        output_subdir: str = "results",
    ) -> None:
        """Generate all configured output formats for a specific detector.

        Args:
            detector_name: Name of the detector that produced the result
            result: Detection results to output
            output_configs: List of output configurations
            target_path: Base path for generating output files
            output_subdir: Subdirectory name for outputs (default: "results")

        Raises:
            OutputError: If output generation fails
        """
        for output_config in output_configs:
            try:
                output_name = output_config.name

                if self.verbose:
                    print_info(f"Generating {output_name} output for {detector_name}")

                # Get and instantiate output plugin
                output_class = get_output(output_name)
                output_instance = output_class()

                # Generate output path
                output_path = self._get_output_path(
                    target_path, output_name, detector_name, output_subdir
                )

                # Create Pydantic config object for this output
                config_class = self.OUTPUT_CONFIG_MAP.get(output_name)
                if config_class:
                    # Create typed config from dict
                    pydantic_config = config_class(**output_config.config)
                else:
                    # Fallback for unknown outputs
                    from pydantic import BaseModel
                    pydantic_config = BaseModel()

                # Write output with Pydantic config
                output_instance.write(
                    result,
                    output_path,
                    pydantic_config
                )

                if self.verbose:
                    print_success(f"Output written: {output_path}")

            except KeyError as e:
                raise PluginError(f"Output plugin error: {e}")
            except Exception as e:
                raise OutputError(
                    f"Output generation failed for {output_name}: {e}"
                )

    def generate_outputs_for_multiple_detectors(
        self,
        results: List[tuple[str, DetectionResult]],
        output_configs: List[OutputConfig],
        target_path: Path,
        output_subdir: str = "results",
    ) -> None:
        """Generate outputs for multiple detector results.

        Args:
            results: List of (detector_name, DetectionResult) tuples
            output_configs: List of output configurations
            target_path: Base path for generating output files
            output_subdir: Subdirectory name for outputs (default: "results")
        """
        for detector_name, result in results:
            self.generate_outputs(
                detector_name=detector_name,
                result=result,
                output_configs=output_configs,
                target_path=target_path,
                output_subdir=output_subdir,
            )

    def _get_output_path(
        self,
        target_path: Path,
        output_name: str,
        detector_name: str,
        output_subdir: str = "results"
    ) -> str:
        """Generate output file path based on target path and output type.

        Args:
            target_path: Base directory path
            output_name: Name of the output plugin
            detector_name: Name of the detector that produced the result
            output_subdir: Subdirectory name for outputs (default: "results")

        Returns:
            Full path to output file
        """
        # Create output subdirectory
        output_dir = target_path / output_subdir
        output_dir.mkdir(parents=True, exist_ok=True)

        base_name = target_path.name

        # Map output types to file extensions
        extensions = {
            'csv': '.csv',
            'json': '.json',
            'html': '.html',
        }

        extension = extensions.get(output_name, f'.{output_name}')

        # Always include detector name to avoid overwrites when running multiple detectors
        return str(output_dir / f"{base_name}_{detector_name}{extension}")

    def get_output_paths_for_detector(
        self,
        target_path: Path,
        detector_name: str,
        output_configs: List[OutputConfig],
    ) -> Dict[str, str]:
        """Get all output paths for a specific detector.

        Args:
            target_path: Base directory path
            detector_name: Name of the detector
            output_configs: List of output configurations

        Returns:
            Dictionary mapping output names to file paths
        """
        paths = {}
        for output_config in output_configs:
            path = self._get_output_path(
                target_path, output_config.name, detector_name
            )
            paths[output_config.name] = path
        return paths
