"""Main orchestration engine for the plugin system."""

from pathlib import Path
from typing import Any, Dict, List, Tuple

from ..core.models.config import AppConfig
from ..core.models.detection import DetectionResult
from ..factories import DetectorFactory, OutputFactory, ProcessorFactory
from ..plugins.models.detectors import JPlagConfig
from ..plugins.models.outputs import CSVOutputConfig, JSONOutputConfig
from ..plugins.models.processors import EncodingNormalizerConfig, NormalizerConfig, UnzipperConfig
from ..services.cleanup import CleanupService
from ..services.output import OutputManager
from ..ui.formatters import print_error, print_info, print_success, print_warning
from .exceptions import DetectionError, PluginError
from .registry import get_detector, get_processor


class PlagiarismDetectionEngine:
    """Main orchestration engine that coordinates the plugin pipeline.

    This engine uses service layer for separation of concerns:
    - OutputManager: Handles output generation
    - CleanupService: Manages temporary file cleanup
    """

    # Map detector names to their Pydantic config classes
    DETECTOR_CONFIG_MAP = {
        'jplag': JPlagConfig,
    }

    # Map processor names to their Pydantic config classes
    PROCESSOR_CONFIG_MAP = {
        'encoding_normalizer': EncodingNormalizerConfig,
        'normalizer': NormalizerConfig,
        'unzipper': UnzipperConfig,
    }

    def __init__(self, config: AppConfig, verbose: bool = False):
        """Initialize the engine with configuration.

        Args:
            config: Application configuration (Pydantic model)
            verbose: Enable verbose output
        """
        self.config = config
        self.verbose = verbose
        self.context: Dict[str, Any] = {'config': config.settings.model_dump()}

        # Initialize factories
        self.detector_factory = DetectorFactory()
        self.output_factory = OutputFactory()
        self.processor_factory = ProcessorFactory()

        # Initialize services
        self.output_manager = OutputManager(verbose=verbose)
        self.cleanup_service = CleanupService(verbose=verbose)

    def run(self) -> None:
        """Execute the complete detection pipeline.

        Supports both single and multiple target paths.
        Each target path gets its own output directory.

        Pipeline stages (per target):
        1. Run pre-detection processors
        2. Run plagiarism detection
        3. Run post-detection processors
        4. Generate outputs (using OutputManager)
        5. Cleanup temporary files (using CleanupService)
        """
        try:
            # Get all target paths (single or multiple)
            target_paths = self.config.settings.get_target_paths()

            if self.verbose:
                print_info(f"Starting plagiarism detection pipeline for {len(target_paths)} project(s)")

            # Process each target path
            for idx, target_path_str in enumerate(target_paths, 1):
                target_path = Path(target_path_str)

                if len(target_paths) > 1:
                    print_info(f"\n{'='*60}")
                    print_info(f"Processing project {idx}/{len(target_paths)}: {target_path}")
                    print_info(f"{'='*60}")

                # Run pipeline for this project
                self._run_pipeline_for_project(target_path)

            if len(target_paths) > 1:
                print_success(f"\n✓ All {len(target_paths)} projects completed successfully!")
            else:
                print_success("Detection pipeline completed successfully")

        except Exception as e:
            print_error(f"Pipeline failed: {e}")
            raise

    def _run_pipeline_for_project(self, target_path: Path) -> None:
        """Execute detection pipeline for a single project.

        Args:
            target_path: Directory containing submissions to analyze
        """
        # Set target_path in context for processors
        self.context['target_path'] = str(target_path)

        # Stage 1: Pre-detection processors
        self._run_processors('pre_detection')

        # Stage 2: Run detections (supports multiple detectors)
        results = self._run_detections(target_path)
        self.context['detection_results'] = results

        # Stage 3: Post-detection processors
        self._run_processors('post_detection')

        # Stage 4: Generate outputs (delegated to OutputManager)
        output_subdir = self.config.settings.output_subdir
        self.output_manager.generate_outputs_for_multiple_detectors(
            results=results,
            output_configs=self.config.outputs,
            target_path=target_path,
            output_subdir=output_subdir,
        )

        # Stage 5: Cleanup
        if self.config.settings.cleanup_temp:
            self.cleanup_service.cleanup_temp_directories()

    def _run_detections(self, target_path: Path) -> List[Tuple[str, DetectionResult]]:
        """Load and run all configured detector plugins.

        Args:
            target_path: Directory containing submissions to analyze

        Returns:
            List of tuples containing (detector_name, DetectionResult)

        Raises:
            DetectionError: If all detectors fail
        """
        results = []

        for detector_config in self.config.detectors:
            try:
                detector_name = detector_config.name

                if self.verbose:
                    print_info(f"Running detector: {detector_name}")

                # Get and instantiate detector plugin
                detector_class = get_detector(detector_name)
                detector = detector_class()

                # Create Pydantic config object for this detector
                config_class = self.DETECTOR_CONFIG_MAP.get(detector_name)
                if config_class:
                    # Create typed config from dict
                    config_dict = detector_config.config.copy()

                    # Inject global base_path if detector doesn't have one
                    global_base_path = self.config.settings.base_path
                    if global_base_path and 'base_path' not in config_dict:
                        config_dict['base_path'] = global_base_path

                    pydantic_config = config_class(**config_dict)
                else:
                    # Fallback for unknown detectors - use base dict
                    from pydantic import BaseModel
                    pydantic_config = BaseModel()

                # Run detection with Pydantic config
                result = detector.detect(
                    target_path=target_path,
                    config=pydantic_config
                )

                if self.verbose:
                    comparison_count = result.get_comparison_count()
                    print_success(
                        f"{detector_name} completed: {comparison_count} comparisons"
                    )

                results.append((detector_name, result))

            except Exception as e:
                print_error(f"{detector_name} failed: {e}")
                if self.verbose:
                    import traceback
                    traceback.print_exc()
                # Continue with other detectors even if one fails
                continue

        if not results:
            raise DetectionError("All detectors failed")

        return results

    def _run_processors(self, stage: str) -> None:
        """Run processors for a specific pipeline stage.

        Args:
            stage: Pipeline stage ('pre_detection' or 'post_detection')
        """
        # Access processors from Pydantic model
        if stage == 'pre_detection':
            processors = self.config.processors.pre_detection
        elif stage == 'post_detection':
            processors = self.config.processors.post_detection
        else:
            return

        for processor_config in processors:
            try:
                processor_name = processor_config.name

                if self.verbose:
                    print_info(f"Running processor ({stage}): {processor_name}")

                # Get and instantiate processor plugin
                processor_class = get_processor(processor_name)
                processor = processor_class()

                # Create Pydantic config object for this processor
                config_class = self.PROCESSOR_CONFIG_MAP.get(processor_name)
                if config_class:
                    # Create typed config from dict
                    pydantic_config = config_class(**processor_config.config)
                else:
                    # Fallback for unknown processors
                    from pydantic import BaseModel
                    pydantic_config = BaseModel()

                # Run processor with Pydantic config
                self.context = processor.process(self.context, pydantic_config)

                if self.verbose:
                    print_success(f"Processor completed: {processor_name}")

            except KeyError as e:
                raise PluginError(f"Processor plugin error: {e}")
            except Exception as e:
                print_warning(f"Processor {processor_name} failed: {e}")
