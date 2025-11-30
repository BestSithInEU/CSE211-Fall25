"""Base factory protocol and exceptions for plugin creation.

This module defines the factory pattern interface for creating plugins with
type-safe configuration validation. Factories provide a clean abstraction layer
between plugin discovery (registry) and plugin instantiation.
"""

from typing import Protocol, TypeVar, Generic, Type, runtime_checkable
from pydantic import BaseModel, ValidationError

from ..core.exceptions import PluginError, ConfigError


# Factory-specific exceptions

class FactoryError(PluginError):
    """Base exception for factory-related errors."""
    pass


class PluginNotFoundError(FactoryError):
    """Raised when requested plugin is not registered."""

    def __init__(self, plugin_type: str, plugin_name: str):
        self.plugin_type = plugin_type
        self.plugin_name = plugin_name
        super().__init__(
            f"{plugin_type} plugin '{plugin_name}' not found in registry. "
            f"Make sure it's properly registered with @register_{plugin_type.lower()}."
        )


class ConfigValidationError(FactoryError, ConfigError):
    """Raised when plugin configuration validation fails."""

    def __init__(self, plugin_name: str, validation_error: ValidationError):
        self.plugin_name = plugin_name
        self.validation_error = validation_error

        # Format Pydantic errors nicely
        errors = validation_error.errors()
        error_details = "\n".join(
            f"  - {err['loc'][0]}: {err['msg']}" for err in errors
        )

        super().__init__(
            f"Configuration validation failed for plugin '{plugin_name}':\n{error_details}"
        )


class PluginInstantiationError(FactoryError):
    """Raised when plugin instantiation fails."""

    def __init__(self, plugin_name: str, reason: str):
        self.plugin_name = plugin_name
        self.reason = reason
        super().__init__(
            f"Failed to instantiate plugin '{plugin_name}': {reason}"
        )


class IncompatibleConfigError(ConfigValidationError):
    """Raised when config type doesn't match plugin requirements."""

    def __init__(self, plugin_name: str, expected_type: Type, got_type: Type):
        self.plugin_name = plugin_name
        self.expected_type = expected_type
        self.got_type = got_type

        # Don't call parent __init__, create custom message
        PluginError.__init__(
            self,
            f"Plugin '{plugin_name}' expects config type {expected_type.__name__}, "
            f"but got {got_type.__name__}"
        )


# Type variables for generic factory

T = TypeVar('T')  # Plugin instance type
ConfigT = TypeVar('ConfigT', bound=BaseModel)  # Config type


# Factory protocol

@runtime_checkable
class PluginFactory(Protocol, Generic[T]):
    """Protocol for plugin factories.

    Factories handle:
    1. Plugin discovery via registry
    2. Configuration validation
    3. Type-safe plugin instantiation
    4. Error handling and reporting

    Type parameter T represents the plugin instance type (e.g., DetectorProtocol).
    """

    def create(self, plugin_name: str, config: BaseModel) -> T:
        """Create a plugin instance with validated configuration.

        Args:
            plugin_name: Name of plugin to instantiate (e.g., 'jplag', 'moss')
            config: Pydantic configuration model for the plugin

        Returns:
            Instantiated plugin instance conforming to protocol T

        Raises:
            PluginNotFoundError: If plugin_name not registered
            ConfigValidationError: If config validation fails
            IncompatibleConfigError: If config type doesn't match plugin
            PluginInstantiationError: If instantiation fails
        """
        ...

    def get_available_plugins(self) -> list[str]:
        """Get list of all registered plugin names.

        Returns:
            List of plugin names available for creation
        """
        ...

    def get_plugin_config_type(self, plugin_name: str) -> Type[BaseModel]:
        """Get expected configuration type for a plugin.

        Args:
            plugin_name: Name of plugin

        Returns:
            Pydantic model type expected by the plugin

        Raises:
            PluginNotFoundError: If plugin not found
        """
        ...

    def validate_config(self, plugin_name: str, config: BaseModel) -> bool:
        """Validate configuration for a plugin without instantiating.

        Args:
            plugin_name: Name of plugin
            config: Configuration to validate

        Returns:
            True if validation succeeds

        Raises:
            PluginNotFoundError: If plugin not found
            ConfigValidationError: If validation fails
            IncompatibleConfigError: If config type incompatible
        """
        ...


# Base factory implementation (concrete class)

class BasePluginFactory(Generic[T]):
    """Abstract base implementation of PluginFactory protocol.

    Provides common functionality for all factory implementations.
    Subclasses must implement _get_plugin_class() method.
    """

    def __init__(self, plugin_type: str):
        """Initialize factory with plugin type identifier.

        Args:
            plugin_type: Human-readable plugin type (e.g., "Detector", "Output")
        """
        self._plugin_type = plugin_type

    def _get_plugin_class(self, plugin_name: str) -> Type[T]:
        """Get plugin class from registry.

        Must be implemented by subclasses to access type-specific registry.

        Args:
            plugin_name: Name of plugin to retrieve

        Returns:
            Plugin class

        Raises:
            PluginNotFoundError: If plugin not found
        """
        raise NotImplementedError("Subclass must implement _get_plugin_class()")

    def _get_all_plugin_names(self) -> list[str]:
        """Get all registered plugin names.

        Must be implemented by subclasses to access type-specific registry.

        Returns:
            List of plugin names
        """
        raise NotImplementedError("Subclass must implement _get_all_plugin_names()")

    def create(self, plugin_name: str, config: BaseModel) -> T:
        """Create plugin instance with validated configuration."""
        # Get plugin class from registry
        plugin_class = self._get_plugin_class(plugin_name)

        # Validate configuration
        self.validate_config(plugin_name, config)

        # Instantiate plugin
        try:
            # Most plugins accept config in constructor or have a setup method
            # We'll try common patterns
            if hasattr(plugin_class, 'from_config'):
                # Factory method pattern
                instance = plugin_class.from_config(config)
            else:
                # Direct instantiation (plugin handles config internally)
                instance = plugin_class()

            return instance
        except Exception as e:
            raise PluginInstantiationError(plugin_name, str(e))

    def get_available_plugins(self) -> list[str]:
        """Get list of all registered plugin names."""
        return self._get_all_plugin_names()

    def get_plugin_config_type(self, plugin_name: str) -> Type[BaseModel]:
        """Get expected configuration type for a plugin."""
        plugin_class = self._get_plugin_class(plugin_name)

        # Try to get config type from plugin class
        if hasattr(plugin_class, 'CONFIG_TYPE'):
            return plugin_class.CONFIG_TYPE

        # Try to infer from type hints
        if hasattr(plugin_class, '__annotations__'):
            for attr_name, attr_type in plugin_class.__annotations__.items():
                if 'config' in attr_name.lower():
                    return attr_type

        # Default to BaseModel if we can't determine
        return BaseModel

    def validate_config(self, plugin_name: str, config: BaseModel) -> bool:
        """Validate configuration for a plugin."""
        plugin_class = self._get_plugin_class(plugin_name)

        # Get expected config type
        expected_type = self.get_plugin_config_type(plugin_name)

        # Check type compatibility
        if not isinstance(config, expected_type) and expected_type != BaseModel:
            raise IncompatibleConfigError(
                plugin_name,
                expected_type,
                type(config)
            )

        # Validate using plugin's validation method if available
        if hasattr(plugin_class, 'validate_config'):
            try:
                plugin_class.validate_config(config)
            except ValueError as e:
                # Convert to our custom exception
                raise ConfigValidationError(plugin_name, e)

        # Pydantic models validate on construction, so if we got here, it's valid
        return True
