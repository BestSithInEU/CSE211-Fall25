"""
Pydantic models for API requests and responses
"""

from typing import List, Optional, Dict, Any
from pydantic import BaseModel, Field


class DetectionRequest(BaseModel):
    """Request to start plagiarism detection"""
    config_path: Optional[str] = Field(None, description="Path to config file")
    detectors: Optional[List[str]] = Field(None, description="Specific detectors to run")
    verbose: bool = Field(False, description="Enable verbose output")


class DetectionJobResponse(BaseModel):
    """Response for detection job creation"""
    job_id: str
    status: str = "pending"
    message: str = "Detection job created"


class ValidationResponse(BaseModel):
    """Response for config validation"""
    valid: bool
    errors: Optional[List[Dict[str, Any]]] = None
    message: Optional[str] = None


class ProjectResponse(BaseModel):
    """Response for project information"""
    id: str
    name: str
    path: str
    reports: List[str] = []
    detectors_run: List[str] = []
    highest_similarity: Optional[float] = None
    last_run: Optional[str] = None


class FileResponse(BaseModel):
    """Response for file content"""
    content: str
    language: str
    filename: str


class CompareResponse(BaseModel):
    """Response for file comparison"""
    file1: str
    file2: str
    content1: str
    content2: str
    language: str


class PluginInfo(BaseModel):
    """Plugin information"""
    name: str
    description: str = ""
    config_type: Optional[str] = None


class PluginsResponse(BaseModel):
    """Response for plugin listing"""
    detectors: List[PluginInfo] = []
    outputs: List[PluginInfo] = []
    processors: List[PluginInfo] = []


class ErrorResponse(BaseModel):
    """Error response"""
    detail: str
    errors: Optional[List[Dict[str, Any]]] = None
