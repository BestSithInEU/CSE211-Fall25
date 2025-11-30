"""Detector plugin factory for type-safe detector creation."""

from typing import Type
from pydantic import BaseModel

from .base import BasePluginFactory, PluginNotFoundError
from ..plugins.protocols import DetectorProtocol
from ..plugins.models.detectors import (
    JPlagConfig,
    MossConfig,
    DolosConfig,
    CopyDetectConfig,
)


class DetectorFactory(BasePluginFactory[DetectorProtocol]):
    """Factory for creating detector plugin instances with validated configurations.

    Integrates with the global detector registry to discover and instantiate
    detector plugins. Ensures type-safe configuration validation before creation.

    Example:
        >>> factory = DetectorFactory()
        >>> jplag_config = JPlagConfig(language="python3", token_length=12)
        >>> detector = factory.create("jplag", jplag_config)
        >>> result = detector.detect("/path/to/submissions", jplag_config)
    """

    # Map detector names to their expected config types
    CONFIG_TYPE_MAP = {
        'jplag': JPlagConfig,
        'moss': MossConfig,
        'dolos': DolosConfig,
        'copydetect': CopyDetectConfig,
    }

    def __init__(self):
        """Initialize detector factory."""
        super().__init__(plugin_type="Detector")
        # Import registry to access detector plugins
        from ..core import registry
        self._registry = registry

    def _get_plugin_class(self, plugin_name: str) -> Type[DetectorProtocol]:
        """Get detector plugin class from registry.

        Args:
            plugin_name: Name of detector plugin

        Returns:
            Detector plugin class

        Raises:
            PluginNotFoundError: If detector not registered
        """
        try:
            return self._registry.get_detector(plugin_name)
        except KeyError:
            raise PluginNotFoundError("Detector", plugin_name)

    def _get_all_plugin_names(self) -> list[str]:
        """Get all registered detector plugin names.

        Returns:
            List of detector names
        """
        # Access the detector registry directly
        return list(self._registry._detector_registry.keys())

    def get_plugin_config_type(self, plugin_name: str) -> Type[BaseModel]:
        """Get expected configuration type for a detector plugin.

        Args:
            plugin_name: Name of detector

        Returns:
            Pydantic model type for this detector's configuration

        Raises:
            PluginNotFoundError: If detector not found
        """
        # First check if detector exists
        self._get_plugin_class(plugin_name)

        # Return mapped config type or default BaseModel
        return self.CONFIG_TYPE_MAP.get(plugin_name, BaseModel)

    def create_with_defaults(self, plugin_name: str, **overrides) -> DetectorProtocol:
        """Create detector with default config and optional overrides.

        Convenience method for creating detectors with minimal configuration.

        Args:
            plugin_name: Name of detector plugin
            **overrides: Override default config values

        Returns:
            Detector plugin instance

        Raises:
            PluginNotFoundError: If detector not found
            ConfigValidationError: If overrides are invalid

        Example:
            >>> factory = DetectorFactory()
            >>> detector = factory.create_with_defaults("jplag", language="java")
        """
        config_type = self.get_plugin_config_type(plugin_name)

        # Create config with defaults + overrides
        config = config_type(**overrides)

        return self.create(plugin_name, config)

    def get_detector_info(self, plugin_name: str) -> dict:
        """Get information about a detector plugin.

        Args:
            plugin_name: Name of detector

        Returns:
            Dictionary with plugin metadata

        Raises:
            PluginNotFoundError: If detector not found
        """
        plugin_class = self._get_plugin_class(plugin_name)
        config_type = self.get_plugin_config_type(plugin_name)

        return {
            'name': plugin_name,
            'class': plugin_class.__name__,
            'module': plugin_class.__module__,
            'config_type': config_type.__name__,
            'docstring': plugin_class.__doc__ or "No description available",
        }

    def list_detectors_with_configs(self) -> dict[str, Type[BaseModel]]:
        """Get mapping of all detectors to their config types.

        Returns:
            Dictionary mapping detector names to config types

        Example:
            >>> factory = DetectorFactory()
            >>> detectors = factory.list_detectors_with_configs()
            >>> print(detectors)
            {'jplag': JPlagConfig, 'moss': MossConfig, ...}
        """
        return {
            name: self.get_plugin_config_type(name)
            for name in self.get_available_plugins()
        }
