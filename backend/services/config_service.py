"""
Service for handling config.yaml operations
"""

import yaml
from pathlib import Path
from typing import Dict, Any, List, Optional
from pydantic import ValidationError

# Import PlagDet's config models
from plagdet.core.config import AppConfig


class ConfigService:
    """Service for config.yaml management"""

    def __init__(self, config_path: str = "config.yaml"):
        # If path is relative, look in parent directory (project root)
        if not Path(config_path).is_absolute():
            # Backend runs from backend/ directory, so go up one level
            self.config_path = Path(__file__).parent.parent.parent / config_path
        else:
            self.config_path = Path(config_path)
        self.base_dir = self.config_path.parent

    def read(self) -> Dict[str, Any]:
        """Read config.yaml and return as dict"""
        if not self.config_path.exists():
            raise FileNotFoundError(f"Config file not found: {self.config_path}")

        with open(self.config_path, 'r') as f:
            return yaml.safe_load(f)

    def read_validated(self) -> AppConfig:
        """Read and validate config using PlagDet's Pydantic model"""
        return AppConfig.load_from_yaml(str(self.config_path))

    def write(self, config_dict: Dict[str, Any]) -> None:
        """Write config dict to config.yaml"""
        with open(self.config_path, 'w') as f:
            yaml.dump(config_dict, f, default_flow_style=False, sort_keys=False)

    def validate(self, config_dict: Dict[str, Any]) -> tuple[bool, Optional[List[Dict[str, Any]]]]:
        """
        Validate config dict against AppConfig model
        Returns: (is_valid, errors_list)
        """
        try:
            AppConfig(**config_dict)
            return True, None
        except ValidationError as e:
            errors = []
            for error in e.errors():
                field = " → ".join(str(loc) for loc in error['loc'])
                errors.append({
                    'field': field,
                    'message': error['msg'],
                    'type': error['type'],
                    'value': error.get('input')
                })
            return False, errors

    def get_schema(self) -> Dict[str, Any]:
        """Get JSON schema for AppConfig model"""
        return AppConfig.model_json_schema()

    def get_target_paths(self) -> List[str]:
        """Get list of target paths from config"""
        config = self.read_validated()
        if hasattr(config.settings, 'target_paths') and config.settings.target_paths:
            return config.settings.target_paths
        elif hasattr(config.settings, 'target_path') and config.settings.target_path:
            return [config.settings.target_path]
        return []
