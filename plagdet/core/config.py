"""Application configuration using Pydantic models.

This module provides a thin wrapper around the Pydantic config models
for backward compatibility and convenience.
"""

# Import all config models from the models module
from .models.config import (
    AppConfig,
    DetectorConfig,
    OutputConfig,
    ProcessorConfig,
    ProcessorsConfig,
    SettingsConfig,
)

# Re-export for backward compatibility
__all__ = [
    "AppConfig",
    "DetectorConfig",
    "OutputConfig",
    "ProcessorConfig",
    "ProcessorsConfig",
    "SettingsConfig",
]
