"""Pydantic models for plugin configurations."""

from .detectors import JPlagConfig
from .outputs import CSVOutputConfig, JSONOutputConfig
from .processors import NormalizerConfig, UnzipperConfig

__all__ = [
    # Detector configs
    "JPlagConfig",
    # Output configs
    "JSONOutputConfig",
    "CSVOutputConfig",
    # Processor configs
    "NormalizerConfig",
    "UnzipperConfig",
]
