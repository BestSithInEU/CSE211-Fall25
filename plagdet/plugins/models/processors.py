"""Pydantic configuration models for processor plugins."""

from pydantic import BaseModel, Field, field_validator


class NormalizerConfig(BaseModel):
    """Configuration for name normalizer processor."""

    strategy: str = Field(
        default="turkish",
        description="Normalization strategy (turkish, simple, or none)",
    )
    preserve_original: bool = Field(
        default=False, description="Keep original names alongside normalized ones"
    )

    @field_validator("strategy")
    @classmethod
    def validate_strategy(cls, v: str) -> str:
        """Validate normalization strategy."""
        valid_strategies = {"turkish", "simple", "none"}
        v_lower = v.lower().strip()
        if v_lower not in valid_strategies:
            raise ValueError(
                f"strategy must be one of {valid_strategies}, got '{v}'"
            )
        return v_lower


class UnzipperConfig(BaseModel):
    """Configuration for unzipper processor."""

    zip_file: str = Field(..., description="Path to ZIP archive to extract")
    extract_to: str = Field(..., description="Directory to extract files to")
    overwrite: bool = Field(
        default=False, description="Overwrite existing files if they exist"
    )
    flatten: bool = Field(
        default=False, description="Flatten directory structure when extracting"
    )
    preserve_permissions: bool = Field(
        default=True, description="Preserve file permissions from archive"
    )

    @field_validator("zip_file")
    @classmethod
    def validate_zip_file(cls, v: str) -> str:
        """Validate zip file path is not empty."""
        if not v or not v.strip():
            raise ValueError("zip_file path cannot be empty")
        return v.strip()

    @field_validator("extract_to")
    @classmethod
    def validate_extract_to(cls, v: str) -> str:
        """Validate extract_to path is not empty."""
        if not v or not v.strip():
            raise ValueError("extract_to path cannot be empty")
        return v.strip()
