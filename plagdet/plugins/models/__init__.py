"""Pydantic models for plugin configurations."""

from .detectors import CopyDetectConfig, DolosConfig, JPlagConfig, MossConfig
from .outputs import CSVOutputConfig, JSONOutputConfig
from .processors import NormalizerConfig, UnzipperConfig

__all__ = [
    # Detector configs
    "JPlagConfig",
    "MossConfig",
    "DolosConfig",
    "CopyDetectConfig",
    # Output configs
    "JSONOutputConfig",
    "CSVOutputConfig",
    # Processor configs
    "NormalizerConfig",
    "UnzipperConfig",
]
