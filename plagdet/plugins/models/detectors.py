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
    # Token normalization (catches variable renaming)
    normalize: Optional[bool] = Field(
        default=None, description="Normalize tokens to catch variable renaming (Java, C++)"
    )
    # Match merging (catches obfuscation)
    match_merging: Optional[bool] = Field(
        default=None, description="Merge neighboring matches to detect obfuscation"
    )
    gap_size: Optional[int] = Field(
        default=None, ge=1, description="Max gap between neighboring matches to merge"
    )
    neighbor_length: Optional[int] = Field(
        default=None, ge=1, description="Min length of neighboring matches to merge"
    )
    required_merges: Optional[int] = Field(
        default=None, ge=1, le=50, description="Min required merges for merging to apply"
    )
    # Clustering options
    cluster_skip: Optional[bool] = Field(
        default=None, description="Skip cluster calculation for performance"
    )
    cluster_algorithm: Optional[str] = Field(
        default=None, description="Clustering algorithm: AGGLOMERATIVE or SPECTRAL"
    )
    cluster_metric: Optional[str] = Field(
        default=None, description="Cluster metric: AVG, MIN, MAX, INTERSECTION"
    )
    # Output options
    similarity_threshold: Optional[float] = Field(
        default=None, ge=0.0, le=1.0, description="Min similarity to save comparisons (0.0-1.0)"
    )
    shown_comparisons: Optional[int] = Field(
        default=None, description="Max comparisons in report (-1 for all)"
    )
    csv_export: Optional[bool] = Field(
        default=None, description="Export pairwise similarity as CSV"
    )
    # Directory modes for comparing old vs new submissions
    new_directories: Optional[List[str]] = Field(
        default=None, description="Current submission directories"
    )
    old_directories: Optional[List[str]] = Field(
        default=None, description="Prior submission directories to compare against"
    )
    # Additional options
    encoding: Optional[str] = Field(
        default=None, description="Submission charset override (disables auto-detection)"
    )
    debug: Optional[bool] = Field(
        default=None, description="Store unparseable files in error folder"
    )
    overwrite: Optional[bool] = Field(
        default=None, description="Overwrite existing result files"
    )
    result_file: Optional[str] = Field(
        default=None, description="Custom result file name (without .zip extension)"
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


