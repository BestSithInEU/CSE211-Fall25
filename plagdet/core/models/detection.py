"""Pydantic models for detection results."""

from typing import Any, Dict, List, Optional

from pydantic import BaseModel, Field, field_validator


class Comparison(BaseModel):
    """A single plagiarism comparison between two submissions."""

    first_submission: str = Field(..., description="First submission identifier")
    second_submission: str = Field(..., description="Second submission identifier")
    similarity: float = Field(
        ..., ge=0.0, le=1.0, description="Similarity score between 0.0 and 1.0"
    )
    metric: str = Field(default="UNKNOWN", description="Similarity metric used")

    # Optional fields for additional metrics (detector-specific)
    longest_fragment: Optional[int] = Field(
        default=None, description="Longest matching fragment (tokens/lines)"
    )
    total_overlap: Optional[int] = Field(
        default=None, description="Total overlap (tokens/lines)"
    )
    similarity1: Optional[float] = Field(
        default=None, ge=0.0, le=1.0, description="First submission similarity (MOSS)"
    )
    similarity2: Optional[float] = Field(
        default=None, ge=0.0, le=1.0, description="Second submission similarity (MOSS)"
    )

    # Additional metadata
    extra: Dict[str, Any] = Field(
        default_factory=dict, description="Additional detector-specific data"
    )

    @field_validator("first_submission", "second_submission")
    @classmethod
    def validate_submission_names(cls, v: str) -> str:
        """Validate submission names are not empty."""
        if not v or not v.strip():
            raise ValueError("Submission name cannot be empty")
        return v.strip()

    @field_validator("similarity")
    @classmethod
    def validate_similarity(cls, v: float) -> float:
        """Ensure similarity is within valid range."""
        if v < 0.0 or v > 1.0:
            raise ValueError(f"Similarity must be between 0.0 and 1.0, got {v}")
        return v

    def to_dict(self) -> Dict[str, Any]:
        """Export comparison to dictionary for backward compatibility.

        Returns:
            Dictionary representation with all non-None fields
        """
        return self.model_dump(exclude_none=True)

    def get_similarity_percentage(self) -> float:
        """Get similarity as percentage (0-100).

        Returns:
            Similarity score as percentage
        """
        return self.similarity * 100.0


class DetectionResult(BaseModel):
    """Results from plagiarism detection.

    Contains a list of comparisons between submissions along with metadata
    about the detection run.
    """

    comparisons: List[Comparison] = Field(
        default_factory=list, description="List of plagiarism comparisons"
    )
    metadata: Dict[str, Any] = Field(
        default_factory=dict, description="Metadata about the detection run"
    )
    raw_data: Optional[Any] = Field(
        default=None, description="Raw detector output (for debugging)"
    )

    class Config:
        """Pydantic configuration."""

        arbitrary_types_allowed = True  # Allow raw_data to be any type

    @field_validator("comparisons")
    @classmethod
    def validate_comparisons(cls, v: List[Comparison]) -> List[Comparison]:
        """Validate comparisons list."""
        # Note: Empty list is valid (no matches found)
        return v

    def filter_by_threshold(self, threshold: float) -> "DetectionResult":
        """Filter comparisons by similarity threshold.

        Args:
            threshold: Minimum similarity score (0.0-1.0)

        Returns:
            New DetectionResult with filtered comparisons
        """
        filtered = [comp for comp in self.comparisons if comp.similarity >= threshold]
        return DetectionResult(
            comparisons=filtered, metadata=self.metadata, raw_data=self.raw_data
        )

    def sort_by_similarity(self, descending: bool = True) -> "DetectionResult":
        """Sort comparisons by similarity score.

        Args:
            descending: If True, highest similarity first

        Returns:
            New DetectionResult with sorted comparisons
        """
        sorted_comps = sorted(
            self.comparisons, key=lambda c: c.similarity, reverse=descending
        )
        return DetectionResult(
            comparisons=sorted_comps, metadata=self.metadata, raw_data=self.raw_data
        )

    def get_comparison_count(self) -> int:
        """Get total number of comparisons.

        Returns:
            Number of comparisons
        """
        return len(self.comparisons)

    def get_average_similarity(self) -> float:
        """Calculate average similarity score across all comparisons.

        Returns:
            Average similarity (0.0-1.0), or 0.0 if no comparisons
        """
        if not self.comparisons:
            return 0.0
        return sum(c.similarity for c in self.comparisons) / len(self.comparisons)

    def get_max_similarity(self) -> float:
        """Get maximum similarity score.

        Returns:
            Maximum similarity (0.0-1.0), or 0.0 if no comparisons
        """
        if not self.comparisons:
            return 0.0
        return max(c.similarity for c in self.comparisons)

    def to_dict(self) -> Dict[str, Any]:
        """Export result to dictionary for backward compatibility.

        Returns:
            Dictionary with comparisons as list of dicts
        """
        return {
            "comparisons": [comp.to_dict() for comp in self.comparisons],
            "metadata": self.metadata,
        }
