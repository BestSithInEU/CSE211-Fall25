"""Pydantic configuration models for output plugins."""

from pydantic import BaseModel, Field, field_validator


class JSONOutputConfig(BaseModel):
    """Configuration for JSON output formatter."""

    pretty: bool = Field(default=True, description="Pretty-print JSON with indentation")
    indent: int = Field(default=2, ge=0, le=8, description="Indentation spaces (0-8)")
    include_metadata: bool = Field(
        default=True, description="Include metadata in JSON output"
    )
    min_score: float = Field(
        default=0.0,
        ge=0.0,
        le=100.0,
        description="Minimum similarity score to include (0-100%)",
    )
    include_raw: bool = Field(
        default=False, description="Include raw detector data in output"
    )

    @field_validator("indent")
    @classmethod
    def validate_indent(cls, v: int) -> int:
        """Validate indent is reasonable."""
        if v < 0:
            raise ValueError("indent must be non-negative")
        if v > 8:
            raise ValueError("indent should not exceed 8 spaces")
        return v

    @field_validator("min_score")
    @classmethod
    def validate_min_score(cls, v: float) -> float:
        """Validate min_score is in valid range."""
        if v < 0.0 or v > 100.0:
            raise ValueError("min_score must be between 0.0 and 100.0")
        return v


class CSVOutputConfig(BaseModel):
    """Configuration for CSV output formatter."""

    min_score: float = Field(
        default=0.0,
        ge=0.0,
        le=100.0,
        description="Minimum similarity score to include (0-100%)",
    )
    metric: str = Field(
        default="AVG",
        description="Similarity metric to use (AVG or MAX)",
    )
    include_unique_names: bool = Field(
        default=False,
        description="Include unique submission names column (for Turkish character handling)",
    )
    delimiter: str = Field(default=",", description="CSV delimiter character")
    include_header: bool = Field(default=True, description="Include CSV header row")
    sort_by_similarity: bool = Field(
        default=True, description="Sort results by similarity (descending)"
    )

    @field_validator("min_score")
    @classmethod
    def validate_min_score(cls, v: float) -> float:
        """Validate min_score is in valid range."""
        if v < 0.0 or v > 100.0:
            raise ValueError("min_score must be between 0.0 and 100.0")
        return v

    @field_validator("metric")
    @classmethod
    def validate_metric(cls, v: str) -> str:
        """Validate metric is valid option."""
        valid_metrics = {"AVG", "MAX", "MIN"}
        v_upper = v.upper().strip()
        if v_upper not in valid_metrics:
            raise ValueError(f"metric must be one of {valid_metrics}, got '{v}'")
        return v_upper

    @field_validator("delimiter")
    @classmethod
    def validate_delimiter(cls, v: str) -> str:
        """Validate delimiter is single character."""
        if len(v) != 1:
            raise ValueError("delimiter must be a single character")
        return v
