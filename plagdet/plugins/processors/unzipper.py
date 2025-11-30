"""Unzipper processor plugin for extracting submission archives."""

import os
import zipfile
from typing import Any, Dict

from pydantic import BaseModel

from ..base import ProcessorPlugin
from ..models.processors import UnzipperConfig
from ...core.registry import register_processor
from ...ui.formatters import print_info, print_success


@register_processor
class UnzipperProcessor(ProcessorPlugin):
    """Processor to unzip student submission archives."""

    # Specify expected config type for validation
    CONFIG_TYPE = UnzipperConfig

    @property
    def name(self) -> str:
        """Plugin identifier."""
        return "unzipper"

    def process(self, context: Dict[str, Any], config: BaseModel) -> Dict[str, Any]:
        """Unzip submissions from a ZIP file.

        Args:
            context: Pipeline context
            config: UnzipperConfig with extraction parameters

        Returns:
            Updated context
        """
        # Type-safe config access
        unzip_config = config if isinstance(config, UnzipperConfig) else UnzipperConfig(**config.model_dump())

        zip_file = unzip_config.zip_file
        extract_to = unzip_config.extract_to

        print_info(f"Unzipping submissions from {zip_file}...")

        # Create output directory
        os.makedirs(extract_to, exist_ok=True)

        # Extract all files
        try:
            with zipfile.ZipFile(zip_file, 'r') as zip_ref:
                zip_ref.extractall(extract_to)

            print_success(f"Successfully extracted submissions to {extract_to}")

            # Update context with extraction info
            context['unzipped_to'] = extract_to

        except Exception as e:
            raise RuntimeError(f"Failed to unzip submissions: {e}")

        return context
