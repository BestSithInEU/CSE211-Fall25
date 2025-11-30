"""Factory pattern implementations for type-safe plugin creation.

This module provides factories for creating detector, output, and processor plugins
with strict configuration validation and type safety.
"""

from .base import (
    PluginFactory,
    BasePluginFactory,
    # Exceptions
    FactoryError,
    PluginNotFoundError,
    ConfigValidationError,
    PluginInstantiationError,
    IncompatibleConfigError,
)
from .detector_factory import DetectorFactory
from .output_factory import OutputFactory
from .processor_factory import ProcessorFactory

__all__ = [
    # Protocols and base classes
    'PluginFactory',
    'BasePluginFactory',
    # Concrete factories
    'DetectorFactory',
    'OutputFactory',
    'ProcessorFactory',
    # Exceptions
    'FactoryError',
    'PluginNotFoundError',
    'ConfigValidationError',
    'PluginInstantiationError',
    'IncompatibleConfigError',
]
