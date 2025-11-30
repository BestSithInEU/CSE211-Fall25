"""Processor plugin factory for type-safe processor creation."""

from typing import Type
from pydantic import BaseModel

from .base import BasePluginFactory, PluginNotFoundError
from ..plugins.protocols import ProcessorProtocol
from ..plugins.models.processors import NormalizerConfig, UnzipperConfig


class ProcessorFactory(BasePluginFactory[ProcessorProtocol]):
    """Factory for creating processor plugin instances with validated configurations.

    Integrates with the global processor registry to discover and instantiate
    processor plugins for pre/post processing. Ensures type-safe configuration.

    Example:
        >>> factory = ProcessorFactory()
        >>> unzip_config = UnzipperConfig(
        ...     zip_file="/path/to/archive.zip",
        ...     extract_to="/path/to/extract"
        ... )
        >>> processor = factory.create("unzipper", unzip_config)
        >>> context = processor.process(context, unzip_config)
    """

    # Map processor names to their expected config types
    CONFIG_TYPE_MAP = {
        'normalizer': NormalizerConfig,
        'unzipper': UnzipperConfig,
    }

    def __init__(self):
        """Initialize processor factory."""
        super().__init__(plugin_type="Processor")
        # Import registry to access processor plugins
        from ..core import registry
        self._registry = registry

    def _get_plugin_class(self, plugin_name: str) -> Type[ProcessorProtocol]:
        """Get processor plugin class from registry.

        Args:
            plugin_name: Name of processor plugin

        Returns:
            Processor plugin class

        Raises:
            PluginNotFoundError: If processor not registered
        """
        try:
            return self._registry.get_processor(plugin_name)
        except KeyError:
            raise PluginNotFoundError("Processor", plugin_name)

    def _get_all_plugin_names(self) -> list[str]:
        """Get all registered processor plugin names.

        Returns:
            List of processor names
        """
        return list(self._registry._processor_registry.keys())

    def get_plugin_config_type(self, plugin_name: str) -> Type[BaseModel]:
        """Get expected configuration type for a processor plugin.

        Args:
            plugin_name: Name of processor

        Returns:
            Pydantic model type for this processor's configuration

        Raises:
            PluginNotFoundError: If processor not found
        """
        # First check if processor exists
        self._get_plugin_class(plugin_name)

        # Return mapped config type or default BaseModel
        return self.CONFIG_TYPE_MAP.get(plugin_name, BaseModel)

    def create_with_defaults(self, plugin_name: str, **overrides) -> ProcessorProtocol:
        """Create processor with default config and optional overrides.

        Convenience method for creating processors with minimal configuration.

        Args:
            plugin_name: Name of processor plugin
            **overrides: Override default config values

        Returns:
            Processor plugin instance

        Raises:
            PluginNotFoundError: If processor not found
            ConfigValidationError: If overrides are invalid

        Example:
            >>> factory = ProcessorFactory()
            >>> processor = factory.create_with_defaults(
            ...     "normalizer",
            ...     strategy="turkish"
            ... )
        """
        config_type = self.get_plugin_config_type(plugin_name)

        # Create config with defaults + overrides
        config = config_type(**overrides)

        return self.create(plugin_name, config)

    def get_processor_info(self, plugin_name: str) -> dict:
        """Get information about a processor plugin.

        Args:
            plugin_name: Name of processor

        Returns:
            Dictionary with plugin metadata

        Raises:
            PluginNotFoundError: If processor not found
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

    def list_processors_with_configs(self) -> dict[str, Type[BaseModel]]:
        """Get mapping of all processors to their config types.

        Returns:
            Dictionary mapping processor names to config types

        Example:
            >>> factory = ProcessorFactory()
            >>> processors = factory.list_processors_with_configs()
            >>> print(processors)
            {'normalizer': NormalizerConfig, 'unzipper': UnzipperConfig}
        """
        return {
            name: self.get_plugin_config_type(name)
            for name in self.get_available_plugins()
        }
