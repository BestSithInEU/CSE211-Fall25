"""Pydantic configuration models for detector plugins."""

from typing import List, Optional

from pydantic import BaseModel, Field, field_validator


class JPlagConfig(BaseModel):
    """Configuration for JPlag detector plugin."""

    language: str = Field(
        default="python3",
        description="Programming language to analyze (e.g., python3, java, c, cpp)",
    )
    token_length: int = Field(
        default=10, ge=1, description="Minimum token length for matching"
    )
    base_path: Optional[str] = Field(
        default=None, description="Optional path to base code to exclude from detection"
    )
    subdirectory: Optional[str] = Field(
        default=None, description="Optional subdirectory within submissions to analyze"
    )
    suffixes: Optional[List[str]] = Field(
        default=None, description="File suffixes to include (e.g., ['.py', '.java'])"
    )
    exclude_files: Optional[List[str]] = Field(
        default=None, description="File patterns to exclude"
    )
    min_token_match: Optional[int] = Field(
        default=None, ge=1, description="Minimum number of tokens required for a match"
    )

    @field_validator("language")
    @classmethod
    def validate_language(cls, v: str) -> str:
        """Validate language is not empty."""
        if not v or not v.strip():
            raise ValueError("JPlag language cannot be empty")
        return v.strip().lower()

    @field_validator("token_length")
    @classmethod
    def validate_token_length(cls, v: int) -> int:
        """Validate token length is reasonable."""
        if v < 1:
            raise ValueError("token_length must be at least 1")
        if v > 100:
            raise ValueError("token_length seems unusually large (>100)")
        return v


class MossConfig(BaseModel):
    """Configuration for MOSS (Measure of Software Similarity) detector plugin."""

    userid: str = Field(..., description="MOSS user ID (required from Stanford)")
    language: str = Field(
        default="python",
        description="Programming language (c, cc, java, python, javascript, etc.)",
    )
    extensions: List[str] = Field(
        default_factory=lambda: ["py"], description="File extensions to include"
    )
    base_files: List[str] = Field(
        default_factory=list, description="Base/template files to exclude from detection"
    )
    max_matches: int = Field(
        default=10, ge=1, description="Maximum matches before submission is ignored"
    )
    comment_string: Optional[str] = Field(
        default=None, description="Comment string for experimental mode"
    )
    experimental: bool = Field(
        default=False, description="Enable MOSS experimental server"
    )
    base_path: Optional[str] = Field(
        default=None, description="Base code directory to exclude from detection"
    )

    @field_validator("userid")
    @classmethod
    def validate_userid(cls, v: str) -> str:
        """Validate MOSS user ID is not empty."""
        if not v or not v.strip():
            raise ValueError(
                "MOSS userid is required. Register at http://moss.stanford.edu/"
            )
        return v.strip()

    @field_validator("language")
    @classmethod
    def validate_language(cls, v: str) -> str:
        """Validate language is not empty."""
        if not v or not v.strip():
            raise ValueError("MOSS language cannot be empty")
        return v.strip().lower()

    @field_validator("extensions")
    @classmethod
    def validate_extensions(cls, v: List[str]) -> List[str]:
        """Validate extensions list is not empty."""
        if not v:
            raise ValueError("extensions list cannot be empty")
        return [ext.strip() for ext in v]

    @field_validator("max_matches")
    @classmethod
    def validate_max_matches(cls, v: int) -> int:
        """Validate max_matches is reasonable."""
        if v < 1:
            raise ValueError("max_matches must be at least 1")
        if v > 1000:
            raise ValueError("max_matches seems unusually large (>1000)")
        return v


class DolosConfig(BaseModel):
    """Configuration for Dolos detector plugin."""

    language: str = Field(
        default="python", description="Programming language to analyze"
    )
    file_pattern: Optional[str] = Field(
        default=None, description="Glob pattern for files to include (e.g., '**/*.py')"
    )
    file_patterns: Optional[List[str]] = Field(
        default=None,
        description="List of glob patterns for files (e.g., ['**/*.tpp', '**/*.cpp']). Takes precedence over file_pattern.",
    )
    min_similarity: float = Field(
        default=0.0,
        ge=0.0,
        le=1.0,
        description="Minimum similarity threshold for reporting (0.0-1.0)",
    )
    output_dir: str = Field(
        default="dolos-report", description="Directory for Dolos web interface output"
    )
    ignore_patterns: Optional[List[str]] = Field(
        default=None, description="Patterns to ignore (e.g., ['test_*', '__pycache__'])"
    )
    base_path: Optional[str] = Field(
        default=None, description="Base code directory to exclude from detection"
    )

    @field_validator("language")
    @classmethod
    def validate_language(cls, v: str) -> str:
        """Validate language is not empty."""
        if not v or not v.strip():
            raise ValueError("Dolos language cannot be empty")
        return v.strip().lower()

    @field_validator("min_similarity")
    @classmethod
    def validate_min_similarity(cls, v: float) -> float:
        """Ensure similarity threshold is valid."""
        if v < 0.0 or v > 1.0:
            raise ValueError("min_similarity must be between 0.0 and 1.0")
        return v

    @field_validator("output_dir")
    @classmethod
    def validate_output_dir(cls, v: str) -> str:
        """Validate output directory is not empty."""
        if not v or not v.strip():
            raise ValueError("output_dir cannot be empty")
        return v.strip()


class CopyDetectConfig(BaseModel):
    """Configuration for CopyDetect detector plugin."""

    extensions: List[str] = Field(
        default_factory=lambda: ["py"],
        description="File extensions to analyze (e.g., ['py', 'java'])",
    )
    reference_dirs: List[str] = Field(
        default_factory=list,
        description="Reference directories for comparison (optional)",
    )
    boilerplate_dirs: List[str] = Field(
        default_factory=list,
        description="Directories containing boilerplate code to exclude",
    )
    display_threshold: float = Field(
        default=0.33,
        ge=0.0,
        le=1.0,
        description="Minimum similarity to display (0.0-1.0)",
    )
    noise_threshold: int = Field(
        default=25, ge=0, description="Minimum number of matching characters"
    )
    guarantee_threshold: float = Field(
        default=0.5,
        ge=0.0,
        le=1.0,
        description="Similarity threshold for guaranteed match",
    )
    disable_filtering: bool = Field(
        default=False, description="Disable automatic filtering of dissimilar code"
    )
    disable_autoopen: bool = Field(
        default=True, description="Disable automatic opening of report in browser"
    )
    base_path: Optional[str] = Field(
        default=None, description="Base code directory to exclude from detection"
    )

    @field_validator("extensions")
    @classmethod
    def validate_extensions(cls, v: List[str]) -> List[str]:
        """Validate extensions list is not empty."""
        if not v:
            raise ValueError("extensions list cannot be empty")
        return [ext.strip() for ext in v]

    @field_validator("display_threshold", "guarantee_threshold")
    @classmethod
    def validate_threshold(cls, v: float) -> float:
        """Ensure threshold is valid."""
        if v < 0.0 or v > 1.0:
            raise ValueError("Threshold must be between 0.0 and 1.0")
        return v

    @field_validator("noise_threshold")
    @classmethod
    def validate_noise_threshold(cls, v: int) -> int:
        """Ensure noise threshold is non-negative."""
        if v < 0:
            raise ValueError("noise_threshold must be non-negative")
        return v
