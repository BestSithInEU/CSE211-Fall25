"""Pydantic models for application configuration."""

from pathlib import Path
from typing import Any, Dict, List

import yaml
from pydantic import BaseModel, Field, field_validator


class DetectorConfig(BaseModel):
    """Configuration for a single detector plugin."""

    name: str = Field(..., description="Name of the detector plugin")
    config: Dict[str, Any] = Field(
        default_factory=dict, description="Detector-specific configuration"
    )

    @field_validator("name")
    @classmethod
    def validate_name(cls, v: str) -> str:
        """Validate detector name is not empty."""
        if not v or not v.strip():
            raise ValueError("Detector name cannot be empty")
        return v.strip()


class OutputConfig(BaseModel):
    """Configuration for a single output plugin."""

    name: str = Field(..., description="Name of the output plugin")
    config: Dict[str, Any] = Field(
        default_factory=dict, description="Output-specific configuration"
    )

    @field_validator("name")
    @classmethod
    def validate_name(cls, v: str) -> str:
        """Validate output name is not empty."""
        if not v or not v.strip():
            raise ValueError("Output name cannot be empty")
        return v.strip()


class ProcessorConfig(BaseModel):
    """Configuration for a single processor plugin."""

    name: str = Field(..., description="Name of the processor plugin")
    config: Dict[str, Any] = Field(
        default_factory=dict, description="Processor-specific configuration"
    )

    @field_validator("name")
    @classmethod
    def validate_name(cls, v: str) -> str:
        """Validate processor name is not empty."""
        if not v or not v.strip():
            raise ValueError("Processor name cannot be empty")
        return v.strip()


class ProcessorsConfig(BaseModel):
    """Configuration for pre and post-detection processors."""

    pre_detection: List[ProcessorConfig] = Field(
        default_factory=list, description="Processors to run before detection"
    )
    post_detection: List[ProcessorConfig] = Field(
        default_factory=list, description="Processors to run after detection"
    )


class SettingsConfig(BaseModel):
    """Application settings."""

    target_path: str | None = Field(
        default=None,
        description="Single directory containing submissions to analyze (use target_path OR target_paths)"
    )
    target_paths: List[str] | None = Field(
        default=None,
        description="Multiple directories to analyze (use target_path OR target_paths)"
    )
    auto_aggregate: bool = Field(
        default=True,
        description="Automatically aggregate results when multiple detectors run",
    )
    cleanup_temp: bool = Field(
        default=False, description="Clean up temporary files after detection"
    )
    verbose: bool = Field(default=False, description="Enable verbose output")
    output_subdir: str = Field(
        default="results",
        description="Subdirectory name for output files (relative to each target path)"
    )
    base_path: str | None = Field(
        default=None,
        description="Global base code directory (relative to target_path) to exclude from detection"
    )

    @field_validator("target_path")
    @classmethod
    def validate_target_path(cls, v: str | None) -> str | None:
        """Validate target_path is not empty if provided."""
        if v is not None and (not v or not v.strip()):
            raise ValueError("target_path cannot be empty string")
        return v.strip() if v else None

    @field_validator("target_paths")
    @classmethod
    def validate_target_paths(cls, v: List[str] | None) -> List[str] | None:
        """Validate target_paths list if provided."""
        if v is not None:
            if not v:
                raise ValueError("target_paths cannot be empty list")
            # Strip whitespace from each path
            return [p.strip() for p in v if p and p.strip()]
        return None

    def model_post_init(self, __context) -> None:
        """Validate that exactly one of target_path or target_paths is provided."""
        if self.target_path is None and self.target_paths is None:
            raise ValueError("Must provide either 'target_path' or 'target_paths'")
        if self.target_path is not None and self.target_paths is not None:
            raise ValueError("Cannot provide both 'target_path' and 'target_paths' - use one or the other")

    def get_target_paths(self) -> List[str]:
        """Get list of target paths (normalizes single path to list).

        Returns:
            List of target directory paths
        """
        if self.target_paths is not None:
            return self.target_paths
        elif self.target_path is not None:
            return [self.target_path]
        else:
            raise ValueError("No target paths configured")


class AppConfig(BaseModel):
    """Complete application configuration loaded from YAML."""

    detectors: List[DetectorConfig] = Field(
        ..., description="List of detector plugins to run", min_length=1
    )
    outputs: List[OutputConfig] = Field(
        ..., description="List of output formats to generate", min_length=1
    )
    processors: ProcessorsConfig = Field(
        default_factory=ProcessorsConfig, description="Pipeline processors"
    )
    settings: SettingsConfig = Field(..., description="Application settings")

    @field_validator("detectors")
    @classmethod
    def validate_detectors(cls, v: List[DetectorConfig]) -> List[DetectorConfig]:
        """Validate detectors list is not empty."""
        if not v:
            raise ValueError("detectors list cannot be empty")
        return v

    @field_validator("outputs")
    @classmethod
    def validate_outputs(cls, v: List[OutputConfig]) -> List[OutputConfig]:
        """Validate outputs list is not empty."""
        if not v:
            raise ValueError("outputs list cannot be empty")
        return v

    @classmethod
    def load_from_yaml(cls, config_path: str) -> "AppConfig":
        """Load configuration from YAML file.

        Args:
            config_path: Path to YAML configuration file

        Returns:
            AppConfig instance with validated configuration

        Raises:
            FileNotFoundError: If config file doesn't exist
            ValueError: If config file is empty or invalid
            ValidationError: If config doesn't match schema
        """
        config_file = Path(config_path)

        if not config_file.exists():
            raise FileNotFoundError(f"Config file not found: {config_path}")

        with open(config_file, "r", encoding="utf-8") as f:
            data = yaml.safe_load(f)

        if data is None:
            raise ValueError(f"Config file is empty: {config_path}")

        # Validate and instantiate using Pydantic (no migration - breaking changes allowed)
        return cls.model_validate(data)

    def to_dict(self) -> Dict[str, Any]:
        """Export configuration to dictionary.

        Returns:
            Dictionary representation of configuration
        """
        return self.model_dump()

    def to_yaml(self, output_path: str) -> None:
        """Export configuration to YAML file.

        Args:
            output_path: Path to write YAML file
        """
        with open(output_path, "w", encoding="utf-8") as f:
            yaml.safe_dump(self.to_dict(), f, default_flow_style=False, sort_keys=False)
