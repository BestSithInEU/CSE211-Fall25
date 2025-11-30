"""Custom exceptions for plagdet."""


class PlagDetError(Exception):
    """Base exception for all plagdet errors."""
    pass


class PluginError(PlagDetError):
    """Plugin-related errors (loading, registration, execution)."""
    pass


class ConfigError(PlagDetError):
    """Configuration errors (invalid YAML, missing fields, etc.)."""
    pass


class DetectionError(PlagDetError):
    """Errors during plagiarism detection process."""
    pass


class OutputError(PlagDetError):
    """Errors during output generation."""
    pass


class ProcessingError(PlagDetError):
    """Errors during pipeline processing."""
    pass


# Note: Factory exceptions (FactoryError, PluginNotFoundError, etc.)
# are defined in plagdet.factories.base to avoid circular imports.
# Import them directly from there if needed:
#   from plagdet.factories.base import FactoryError, PluginNotFoundError, etc.

__all__ = [
    'PlagDetError',
    'PluginError',
    'ConfigError',
    'DetectionError',
    'OutputError',
    'ProcessingError',
]
