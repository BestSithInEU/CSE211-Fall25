"""Name normalizer processor plugin for standardizing student names."""

from typing import Any, Dict

import unidecode
from pydantic import BaseModel

from ..base import ProcessorPlugin
from ..models.processors import NormalizerConfig
from ...core.registry import register_processor
from ...ui.formatters import print_info, print_success


@register_processor
class NameNormalizer(ProcessorPlugin):
    """Processor to normalize student names in detection results."""

    # Specify expected config type for validation
    CONFIG_TYPE = NormalizerConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "normalizer"

    def process(self, context: Dict[str, Any], config: BaseModel) -> Dict[str, Any]:
        """Normalize student names in detection results.

        Args:
            context: Pipeline context containing detection_result
            config: NormalizerConfig with normalization strategy

        Returns:
            Updated context with normalized names
        """
        result = context.get('detection_result')
        if not result:
            # If no detection result yet (pre-detection), just pass through
            return context

        # Type-safe config access
        norm_config = config if isinstance(config, NormalizerConfig) else NormalizerConfig(**config.model_dump())

        strategy = norm_config.strategy

        print_info(f"Normalizing names using strategy: {strategy}")

        # Normalize all submission names in comparisons
        for comparison in result.comparisons:
            comparison['first_submission'] = self._normalize(
                comparison['first_submission'],
                strategy
            )
            comparison['second_submission'] = self._normalize(
                comparison['second_submission'],
                strategy
            )

        print_success("Name normalization completed")

        return context

    def _normalize(self, name: str, strategy: str) -> str:
        """Normalize a single name based on strategy.

        Args:
            name: Name to normalize
            strategy: Normalization strategy

        Returns:
            Normalized name
        """
        if strategy == 'turkish':
            return self._normalize_turkish(name)
        elif strategy == 'simple':
            return self._normalize_simple(name)
        else:
            return name  # No normalization

    def _normalize_turkish(self, name: str) -> str:
        """Normalize Turkish characters in student names.

        Args:
            name: Name to normalize

        Returns:
            Normalized name with Turkish characters converted
        """
        # Turkish character replacements
        replacements = {
            'Ç': 'C', 'ç': 'c',
            'Ğ': 'G', 'ğ': 'g',
            'İ': 'I', 'ı': 'i',
            'Ö': 'O', 'ö': 'o',
            'Ş': 'S', 'ş': 's',
            'Ü': 'U', 'ü': 'u',
        }

        # Apply Turkish replacements
        for original, replacement in replacements.items():
            name = name.replace(original, replacement)

        # Apply unidecode for any remaining special characters
        # and extract just the first part (before underscore)
        name = unidecode.unidecode(name.split('_')[0])

        return name

    def _normalize_simple(self, name: str) -> str:
        """Simple normalization - just ASCII conversion.

        Args:
            name: Name to normalize

        Returns:
            ASCII-only name
        """
        return unidecode.unidecode(name)
