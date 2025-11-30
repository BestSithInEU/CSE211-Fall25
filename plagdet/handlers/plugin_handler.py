"""Handler for plugin management operations."""

from ..core.registry import list_all_plugins


class PluginHandler:
    """Handler for plugin-related operations.

    Provides methods for listing and querying available plugins.
    """

    def list_all(self) -> None:
        """List all registered plugins with formatted output.

        Displays a table of all available detectors, outputs,
        and processors with their status.
        """
        list_all_plugins()

    def get_plugin_info(self) -> dict:
        """Get structured information about all plugins.

        Returns:
            Dictionary with plugin counts and lists:
            {
                'detectors': ['jplag', 'moss', ...],
                'outputs': ['csv', 'json'],
                'processors': ['unzipper', 'normalizer'],
                'total': 8
            }
        """
        from ..core.registry import (
            _detector_registry,
            _output_registry,
            _processor_registry
        )

        detectors = sorted(_detector_registry.keys())
        outputs = sorted(_output_registry.keys())
        processors = sorted(_processor_registry.keys())

        return {
            'detectors': detectors,
            'outputs': outputs,
            'processors': processors,
            'total': len(detectors) + len(outputs) + len(processors)
        }

    def plugin_exists(self, plugin_type: str, plugin_name: str) -> bool:
        """Check if a plugin exists.

        Args:
            plugin_type: Type of plugin ('detector', 'output', or 'processor')
            plugin_name: Name of the plugin

        Returns:
            True if plugin is registered, False otherwise
        """
        from ..core.registry import (
            _detector_registry,
            _output_registry,
            _processor_registry
        )

        registries = {
            'detector': _detector_registry,
            'output': _output_registry,
            'processor': _processor_registry
        }

        registry = registries.get(plugin_type)
        if registry is None:
            return False

        return plugin_name in registry
