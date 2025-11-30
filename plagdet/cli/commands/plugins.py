"""Plugins command - List available plugins."""

from ...handlers.plugin_handler import PluginHandler


def list_plugins_command():
    """List all available plugins.

    Shows registered detectors, outputs, and processors with details.

    [cyan]Example:[/cyan]
        plagdet list-plugins
    """
    handler = PluginHandler()
    handler.list_all()
