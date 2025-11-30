"""Base classes for all plugin types.

These base classes provide concrete implementations that satisfy the Protocol interfaces
defined in protocols.py. Plugins can inherit from these base classes to get default
implementations of lifecycle methods and validation.
"""

from abc import ABC, abstractmethod
from typing import Any, Dict
from pathlib import Path

from pydantic import BaseModel, ValidationError

from ..core.models.detection import DetectionResult
from ..core.exceptions import ConfigError


class DetectorPlugin(ABC):
    """Base class for plagiarism detection tools.

    Implements DetectorProtocol with default lifecycle methods.
    Subclasses must implement detect() and name property.
    """

    # Subclasses can override to specify expected config type
    CONFIG_TYPE: type[BaseModel] = BaseModel

    @abstractmethod
    def detect(self, target_path: str | Path, config: BaseModel) -> DetectionResult:
        """Run detection and return results.

        Args:
            target_path: Path to the directory containing submissions
            config: Type-specific Pydantic configuration model

        Returns:
            DetectionResult (Pydantic model) containing typed comparisons and metadata

        Raises:
            DetectionError: If detection process fails
        """
        pass

    @property
    @abstractmethod
    def name(self) -> str:
        """Plugin identifier used in config files."""
        pass

    def validate_config(self, config: BaseModel) -> bool:
        """Validate plugin configuration.

        Default implementation checks if config is instance of expected CONFIG_TYPE.

        Args:
            config: Configuration to validate

        Returns:
            True if valid

        Raises:
            ConfigError: If validation fails
        """
        if not isinstance(config, self.CONFIG_TYPE):
            raise ConfigError(
                f"{self.name} expects config type {self.CONFIG_TYPE.__name__}, "
                f"got {type(config).__name__}"
            )

        # Pydantic models self-validate, so if we got here it's valid
        return True

    def cleanup(self) -> None:
        """Clean up temporary files and resources.

        Default implementation does nothing. Override if needed.
        """
        pass


class OutputPlugin(ABC):
    """Base class for output formatters.

    Implements OutputProtocol with default lifecycle methods.
    Subclasses must implement write() and name property.
    """

    # Subclasses can override to specify expected config type
    CONFIG_TYPE: type[BaseModel] = BaseModel

    @abstractmethod
    def write(
        self,
        result: DetectionResult,
        output_path: str | Path,
        config: BaseModel
    ) -> None:
        """Write detection results to output.

        Args:
            result: Detection results (Pydantic model) to format
            output_path: Path to write the output file
            config: Type-specific Pydantic configuration model

        Raises:
            OutputError: If writing fails
        """
        pass

    @property
    @abstractmethod
    def name(self) -> str:
        """Plugin identifier used in config files."""
        pass

    def validate_config(self, config: BaseModel) -> bool:
        """Validate plugin configuration.

        Default implementation checks if config is instance of expected CONFIG_TYPE.

        Args:
            config: Configuration to validate

        Returns:
            True if valid

        Raises:
            ConfigError: If validation fails
        """
        if not isinstance(config, self.CONFIG_TYPE):
            raise ConfigError(
                f"{self.name} expects config type {self.CONFIG_TYPE.__name__}, "
                f"got {type(config).__name__}"
            )

        return True

    def cleanup(self) -> None:
        """Clean up temporary files after output generation.

        Default implementation does nothing. Override if needed.
        """
        pass


class ProcessorPlugin(ABC):
    """Base class for pipeline processors (pre/post processing).

    Implements ProcessorProtocol with default lifecycle methods.
    Subclasses must implement process() and name property.
    """

    # Subclasses can override to specify expected config type
    CONFIG_TYPE: type[BaseModel] = BaseModel

    @abstractmethod
    def process(self, context: Dict[str, Any], config: BaseModel) -> Dict[str, Any]:
        """Process data in the pipeline.

        Args:
            context: Shared context containing detection results and metadata
            config: Type-specific Pydantic configuration model

        Returns:
            Updated context dictionary

        Raises:
            ProcessingError: If processing fails
        """
        pass

    @property
    @abstractmethod
    def name(self) -> str:
        """Plugin identifier used in config files."""
        pass

    def validate_config(self, config: BaseModel) -> bool:
        """Validate plugin configuration.

        Default implementation checks if config is instance of expected CONFIG_TYPE.

        Args:
            config: Configuration to validate

        Returns:
            True if valid

        Raises:
            ConfigError: If validation fails
        """
        if not isinstance(config, self.CONFIG_TYPE):
            raise ConfigError(
                f"{self.name} expects config type {self.CONFIG_TYPE.__name__}, "
                f"got {type(config).__name__}"
            )

        return True

    def cleanup(self) -> None:
        """Clean up temporary files after processing.

        Default implementation does nothing. Override if needed.
        """
        pass
