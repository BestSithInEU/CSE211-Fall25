"""Protocol-based interfaces for type-safe plugin contracts.

This module defines Protocol interfaces that enforce strict typing for plugin implementations.
Unlike ABC-based inheritance, Protocols use structural subtyping (duck typing) for LSP compliance.

Protocols are runtime_checkable for validation and provide clear contracts for plugin behavior.
"""

from typing import Protocol, runtime_checkable, Any, Dict
from pathlib import Path

from pydantic import BaseModel

from ..core.models.detection import DetectionResult


@runtime_checkable
class PluginProtocol(Protocol):
    """Base protocol for all plugins.

    All plugins must implement:
    - name property for identification
    - validate_config method for configuration validation
    """

    @property
    def name(self) -> str:
        """Unique plugin identifier used in configuration files.

        Returns:
            Plugin name (e.g., 'jplag', 'moss', 'csv')
        """
        ...

    def validate_config(self, config: BaseModel) -> bool:
        """Validate plugin configuration.

        Args:
            config: Pydantic configuration model to validate

        Returns:
            True if config is valid for this plugin

        Raises:
            ValueError: If configuration is invalid
        """
        ...


@runtime_checkable
class DetectorProtocol(PluginProtocol, Protocol):
    """Protocol for plagiarism detection plugins.

    Detectors analyze code submissions and return similarity results.
    They must accept a specific Pydantic config model (not **kwargs).

    Example implementations: JPlag, MOSS, Dolos, CopyDetect
    """

    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Execute plagiarism detection on target directory.

        Args:
            target_path: Path to directory containing student submissions
            config: Type-specific Pydantic config (JPlagConfig, MossConfig, etc.)

        Returns:
            DetectionResult containing comparisons and metadata

        Raises:
            DetectionError: If detection process fails
            ConfigValidationError: If config is invalid for this detector
        """
        ...

    def cleanup(self) -> None:
        """Clean up temporary files and resources after detection.

        Optional lifecycle hook. Default implementation does nothing.
        """
        ...


@runtime_checkable
class OutputProtocol(PluginProtocol, Protocol):
    """Protocol for output formatting plugins.

    Output plugins write detection results to files in various formats.
    They must accept a specific Pydantic config model (not **kwargs).

    Example implementations: CSV, JSON
    """

    def write(
        self,
        result: DetectionResult,
        output_path: str | Path,
        config: BaseModel
    ) -> None:
        """Write detection results to output file.

        Args:
            result: DetectionResult (Pydantic model) containing comparisons
            output_path: Path where output file should be written
            config: Type-specific Pydantic config (CSVOutputConfig, JSONOutputConfig, etc.)

        Raises:
            OutputError: If writing fails
            ConfigValidationError: If config is invalid for this output format
        """
        ...

    def cleanup(self) -> None:
        """Clean up temporary files after output generation.

        Optional lifecycle hook. Default implementation does nothing.
        """
        ...


@runtime_checkable
class ProcessorProtocol(PluginProtocol, Protocol):
    """Protocol for pipeline processor plugins.

    Processors transform data in the detection pipeline (pre/post processing).
    They operate on a shared context dictionary.

    Example implementations: Unzipper, Normalizer
    """

    def process(self, context: Dict[str, Any], config: BaseModel) -> Dict[str, Any]:
        """Process data in the detection pipeline.

        Args:
            context: Shared context containing paths, metadata, and results
            config: Type-specific Pydantic config (UnzipperConfig, NormalizerConfig, etc.)

        Returns:
            Updated context dictionary with processed data

        Raises:
            ProcessingError: If processing fails
            ConfigValidationError: If config is invalid for this processor
        """
        ...

    def cleanup(self) -> None:
        """Clean up temporary files after processing.

        Optional lifecycle hook. Default implementation does nothing.
        """
        ...


# Optional capability protocols (mix-ins)

@runtime_checkable
class SupportsCaching(Protocol):
    """Protocol for plugins that support caching results."""

    def cache_key(self, config: BaseModel) -> str:
        """Generate cache key from configuration.

        Args:
            config: Plugin configuration

        Returns:
            Unique cache key string
        """
        ...

    def load_from_cache(self, cache_key: str) -> DetectionResult | None:
        """Load results from cache.

        Args:
            cache_key: Cache key to look up

        Returns:
            Cached DetectionResult or None if not found
        """
        ...

    def save_to_cache(self, cache_key: str, result: DetectionResult) -> None:
        """Save results to cache.

        Args:
            cache_key: Cache key to store under
            result: Detection result to cache
        """
        ...


@runtime_checkable
class SupportsParallel(Protocol):
    """Protocol for plugins that support parallel execution."""

    @property
    def max_workers(self) -> int:
        """Maximum number of parallel workers.

        Returns:
            Number of parallel workers (e.g., CPU count)
        """
        ...

    def detect_parallel(
        self,
        target_paths: list[str | Path],
        config: BaseModel
    ) -> list[DetectionResult]:
        """Execute detection on multiple targets in parallel.

        Args:
            target_paths: List of directories to analyze
            config: Plugin configuration

        Returns:
            List of DetectionResults, one per target
        """
        ...


@runtime_checkable
class SupportsIncremental(Protocol):
    """Protocol for plugins that support incremental analysis."""

    def detect_incremental(
        self,
        target_path: str | Path,
        previous_result: DetectionResult,
        config: BaseModel
    ) -> DetectionResult:
        """Execute detection on only changed files.

        Args:
            target_path: Directory containing submissions
            previous_result: Previous detection result for comparison
            config: Plugin configuration

        Returns:
            Updated DetectionResult with incremental changes
        """
        ...


# Type aliases for convenience

DetectorType = DetectorProtocol
OutputType = OutputProtocol
ProcessorType = ProcessorProtocol
