"""Core Pydantic models for configuration and detection results."""

from .config import (
    AppConfig,
    DetectorConfig,
    OutputConfig,
    ProcessorConfig,
    ProcessorsConfig,
    SettingsConfig,
)
from .detection import Comparison, DetectionResult

__all__ = [
    "AppConfig",
    "DetectorConfig",
    "OutputConfig",
    "ProcessorConfig",
    "ProcessorsConfig",
    "SettingsConfig",
    "Comparison",
    "DetectionResult",
]
