"""Output plugin factory for type-safe output formatter creation."""

from typing import Type
from pydantic import BaseModel

from .base import BasePluginFactory, PluginNotFoundError
from ..plugins.protocols import OutputProtocol
from ..plugins.models.outputs import JSONOutputConfig, CSVOutputConfig


class OutputFactory(BasePluginFactory[OutputProtocol]):
    """Factory for creating output plugin instances with validated configurations.

    Integrates with the global output registry to discover and instantiate
    output formatter plugins. Ensures type-safe configuration validation.

    Example:
        >>> factory = OutputFactory()
        >>> csv_config = CSVOutputConfig(min_score=30.0, metric="AVG")
        >>> output = factory.create("csv", csv_config)
        >>> output.write(detection_result, "/path/to/output.csv", csv_config)
    """

    # Map output names to their expected config types
    CONFIG_TYPE_MAP = {
        'csv': CSVOutputConfig,
        'json': JSONOutputConfig,
    }

    def __init__(self):
        """Initialize output factory."""
        super().__init__(plugin_type="Output")
        # Import registry to access output plugins
        from ..core import registry
        self._registry = registry

    def _get_plugin_class(self, plugin_name: str) -> Type[OutputProtocol]:
        """Get output plugin class from registry.

        Args:
            plugin_name: Name of output plugin

        Returns:
            Output plugin class

        Raises:
            PluginNotFoundError: If output not registered
        """
        try:
            return self._registry.get_output(plugin_name)
        except KeyError:
            raise PluginNotFoundError("Output", plugin_name)

    def _get_all_plugin_names(self) -> list[str]:
        """Get all registered output plugin names.

        Returns:
            List of output names
        """
        return list(self._registry._output_registry.keys())

    def get_plugin_config_type(self, plugin_name: str) -> Type[BaseModel]:
        """Get expected configuration type for an output plugin.

        Args:
            plugin_name: Name of output

        Returns:
            Pydantic model type for this output's configuration

        Raises:
            PluginNotFoundError: If output not found
        """
        # First check if output exists
        self._get_plugin_class(plugin_name)

        # Return mapped config type or default BaseModel
        return self.CONFIG_TYPE_MAP.get(plugin_name, BaseModel)

    def create_with_defaults(self, plugin_name: str, **overrides) -> OutputProtocol:
        """Create output formatter with default config and optional overrides.

        Convenience method for creating outputs with minimal configuration.

        Args:
            plugin_name: Name of output plugin
            **overrides: Override default config values

        Returns:
            Output plugin instance

        Raises:
            PluginNotFoundError: If output not found
            ConfigValidationError: If overrides are invalid

        Example:
            >>> factory = OutputFactory()
            >>> output = factory.create_with_defaults("csv", min_score=50.0)
        """
        config_type = self.get_plugin_config_type(plugin_name)

        # Create config with defaults + overrides
        config = config_type(**overrides)

        return self.create(plugin_name, config)

    def get_output_info(self, plugin_name: str) -> dict:
        """Get information about an output plugin.

        Args:
            plugin_name: Name of output

        Returns:
            Dictionary with plugin metadata

        Raises:
            PluginNotFoundError: If output not found
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

    def list_outputs_with_configs(self) -> dict[str, Type[BaseModel]]:
        """Get mapping of all outputs to their config types.

        Returns:
            Dictionary mapping output names to config types

        Example:
            >>> factory = OutputFactory()
            >>> outputs = factory.list_outputs_with_configs()
            >>> print(outputs)
            {'csv': CSVOutputConfig, 'json': JSONOutputConfig}
        """
        return {
            name: self.get_plugin_config_type(name)
            for name in self.get_available_plugins()
        }
