"""Handler for running plagiarism detection."""

import glob
from pathlib import Path
from typing import Optional

from ..core.config import AppConfig
from ..core.engine import PlagiarismDetectionEngine
from ..core.exceptions import PlagDetError
from ..core.models.config import DetectorConfig
from ..core.registry import _detector_registry
from ..ui.console import console
from ..ui.formatters import print_error, print_info, print_success, print_warning


class RunHandler:
    """Handler for detection execution logic.

    Separates detection orchestration from CLI interface,
    allowing the logic to be tested and reused independently.
    """

    def __init__(self, verbose: bool = False):
        """Initialize handler.

        Args:
            verbose: Enable verbose output
        """
        self.verbose = verbose

    def execute(
        self,
        config_path: str | Path,
        detector_override: Optional[list[str]] = None,
        all_detectors: bool = False
    ) -> None:
        """Execute plagiarism detection.

        Args:
            config_path: Path to YAML configuration file
            detector_override: List of detector names to run (overrides config)
            all_detectors: Run all available detectors (overrides config)

        Raises:
            PlagDetError: If detection fails
            FileNotFoundError: If config file not found
            ValidationError: If config is invalid
        """
        try:
            # Load configuration
            app_config = self._load_config(config_path)

            # Apply detector overrides if provided
            if all_detectors:
                app_config = self._override_all_detectors(app_config)
            elif detector_override:
                app_config = self._override_specific_detectors(app_config, detector_override)

            # Create and run engine
            engine = PlagiarismDetectionEngine(app_config, verbose=self.verbose)
            engine.run()

            print_success("Detection completed successfully")

        except PlagDetError as e:
            print_error(f"Error: {e}")
            raise
        except Exception as e:
            print_error(f"Unexpected error: {e}")
            if self.verbose:
                console.print_exception(show_locals=True)
            raise

    def execute_all(
        self,
        pattern: str = "config-lab*.yaml",
        detector_override: Optional[list[str]] = None,
        all_detectors: bool = False
    ) -> None:
        """Execute plagiarism detection for all matching config files.

        Args:
            pattern: Glob pattern to match config files (default: config-lab*.yaml)
            detector_override: List of detector names to run (overrides config)
            all_detectors: Run all available detectors (overrides config)

        Raises:
            PlagDetError: If detection fails
            FileNotFoundError: If no config files found
        """
        config_files = sorted(glob.glob(pattern))

        if not config_files:
            raise FileNotFoundError(f"No config files found matching: {pattern}")

        print_info(f"Found {len(config_files)} config file(s): {', '.join(config_files)}")

        failed = []
        for config_path in config_files:
            print_info(f"\n{'='*60}")
            print_info(f"Running: {config_path}")
            print_info(f"{'='*60}")

            try:
                self.execute(
                    config_path=config_path,
                    detector_override=detector_override,
                    all_detectors=all_detectors
                )
            except Exception as e:
                print_error(f"Failed: {config_path} - {e}")
                failed.append(config_path)

        # Summary
        print_info(f"\n{'='*60}")
        print_info("SUMMARY")
        print_info(f"{'='*60}")
        print_success(f"Completed: {len(config_files) - len(failed)}/{len(config_files)}")

        if failed:
            print_warning(f"Failed: {', '.join(failed)}")

    def _load_config(self, config_path: str | Path) -> AppConfig:
        """Load and validate configuration file.

        Args:
            config_path: Path to YAML config file

        Returns:
            Validated AppConfig

        Raises:
            FileNotFoundError: If config file doesn't exist
            ValidationError: If config is invalid
        """
        config_str = str(config_path)

        # Check file exists
        if not Path(config_path).exists():
            raise FileNotFoundError(f"Configuration file not found: {config_path}")

        # Load using Pydantic
        return AppConfig.load_from_yaml(config_str)

    def _override_all_detectors(self, config: AppConfig) -> AppConfig:
        """Override config to run all available detectors.

        Args:
            config: Original configuration

        Returns:
            Modified configuration with all detectors
        """
        detector_names = list(_detector_registry.keys())

        # Build map of existing detector configs
        existing_configs = {d.name: d.config for d in config.detectors}

        # Include all detectors, preserving config if available
        config.detectors = [
            DetectorConfig(name=name, config=existing_configs.get(name, {}))
            for name in detector_names
        ]

        print_info(
            f"CLI override: running ALL detectors ({', '.join(detector_names)})"
        )

        return config

    def _override_specific_detectors(
        self,
        config: AppConfig,
        detector_names: list[str]
    ) -> AppConfig:
        """Override config to run specific detectors.

        Args:
            config: Original configuration
            detector_names: List of detector names to run

        Returns:
            Modified configuration with specified detectors
        """
        # Validate detector names exist
        available = set(_detector_registry.keys())
        invalid = [name for name in detector_names if name not in available]

        if invalid:
            raise ValueError(
                f"Invalid detector(s): {', '.join(invalid)}. "
                f"Available: {', '.join(sorted(available))}"
            )

        # Build map of existing detector configs
        existing_configs = {d.name: d.config for d in config.detectors}

        # Filter to requested detectors, preserving their config from the file
        config.detectors = [
            DetectorConfig(name=name, config=existing_configs.get(name, {}))
            for name in detector_names
        ]

        print_info(
            f"CLI override: running detectors ({', '.join(detector_names)})"
        )

        return config

    def validate_detector_names(self, names: list[str]) -> tuple[bool, list[str]]:
        """Validate detector names against registry.

        Args:
            names: Detector names to validate

        Returns:
            Tuple of (all_valid, list_of_invalid_names)
        """
        available = set(_detector_registry.keys())
        invalid = [name for name in names if name not in available]
        return (len(invalid) == 0, invalid)

    def get_available_detectors(self) -> list[str]:
        """Get list of all available detector names.

        Returns:
            List of registered detector names
        """
        return sorted(_detector_registry.keys())
