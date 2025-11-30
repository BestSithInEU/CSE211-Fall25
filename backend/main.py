"""
PlagDet FastAPI Backend
Provides REST API and WebSocket endpoints for the Next.js frontend
"""

import os
import sys
from pathlib import Path

# Add parent directory to path to import plagdet modules
sys.path.insert(0, str(Path(__file__).parent.parent))
# Add backend directory to path for local imports
sys.path.insert(0, str(Path(__file__).parent))

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from routers import config, detection, projects, files

# Configuration from environment variables
BACKEND_HOST = os.getenv("BACKEND_HOST", "0.0.0.0")
BACKEND_PORT = int(os.getenv("BACKEND_PORT", "8000"))
FRONTEND_URL = os.getenv("FRONTEND_URL", "http://localhost:3000")

app = FastAPI(
    title="PlagDet API",
    description="Backend API for PlagDet plagiarism detection tool",
    version="1.0.0"
)

# CORS middleware for Next.js frontend
app.add_middleware(
    CORSMiddleware,
    allow_origins=[FRONTEND_URL, "http://localhost:3000"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# Register routers
app.include_router(config.router, prefix="/api", tags=["config"])
app.include_router(detection.router, prefix="/api", tags=["detection"])
app.include_router(projects.router, prefix="/api", tags=["projects"])
app.include_router(files.router, prefix="/api", tags=["files"])


@app.get("/")
async def root():
    return {
        "message": "PlagDet API",
        "version": "1.0.0",
        "docs": "/docs"
    }


@app.get("/health")
async def health():
    return {"status": "healthy"}


if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host=BACKEND_HOST, port=BACKEND_PORT, reload=True)
