"""
Service for running plagiarism detection
"""

import asyncio
import uuid
from typing import Optional, List, Dict, Any
from pathlib import Path


class DetectionJob:
    """Represents a detection job"""

    def __init__(self, job_id: str, config_path: str, detectors: Optional[List[str]] = None):
        self.job_id = job_id
        self.config_path = config_path
        self.detectors = detectors or []
        self.status = "pending"
        self.output = []
        self.error: Optional[str] = None
        self.process: Optional[asyncio.subprocess.Process] = None

    def to_dict(self) -> Dict[str, Any]:
        return {
            "job_id": self.job_id,
            "status": self.status,
            "output": "\n".join(self.output),
            "error": self.error
        }


class DetectionService:
    """Service for managing plagiarism detection jobs"""

    def __init__(self):
        self.jobs: Dict[str, DetectionJob] = {}

    def create_job(
        self,
        config_path: str = "config.yaml",
        detectors: Optional[List[str]] = None,
        verbose: bool = False
    ) -> str:
        """Create a new detection job and return job_id"""
        job_id = str(uuid.uuid4())
        job = DetectionJob(job_id, config_path, detectors)
        self.jobs[job_id] = job
        return job_id

    def get_job(self, job_id: str) -> Optional[DetectionJob]:
        """Get job by ID"""
        return self.jobs.get(job_id)

    async def run_detection(
        self,
        job_id: str,
        websocket_send=None
    ) -> Dict[str, Any]:
        """
        Run plagiarism detection asynchronously
        Streams output via WebSocket if provided
        """
        job = self.get_job(job_id)
        if not job:
            return {"error": f"Job not found: {job_id}"}

        job.status = "running"

        # Build command
        cmd = ["uv", "run", "plagdet", "run", "-c", job.config_path]

        # Add specific detectors if requested
        for detector in job.detectors:
            cmd.extend(["-d", detector])

        # Add verbose flag
        cmd.append("--verbose")

        try:
            # Send start message
            if websocket_send:
                await websocket_send({
                    "type": "status",
                    "status": "running",
                    "message": f"Starting detection: {' '.join(cmd)}"
                })

            # Start process from project root (parent of backend/)
            project_root = Path(__file__).parent.parent.parent
            job.process = await asyncio.create_subprocess_exec(
                *cmd,
                stdout=asyncio.subprocess.PIPE,
                stderr=asyncio.subprocess.STDOUT,
                cwd=str(project_root)
            )

            # Stream output
            while True:
                line = await job.process.stdout.readline()
                if not line:
                    break

                decoded_line = line.decode('utf-8').rstrip()
                job.output.append(decoded_line)

                # Send via WebSocket
                if websocket_send:
                    await websocket_send({
                        "type": "output",
                        "message": decoded_line
                    })

            # Wait for completion
            await job.process.wait()

            if job.process.returncode == 0:
                job.status = "completed"
                if websocket_send:
                    await websocket_send({
                        "type": "status",
                        "status": "completed",
                        "message": "Detection completed successfully"
                    })
            else:
                job.status = "failed"
                job.error = f"Process exited with code {job.process.returncode}"
                if websocket_send:
                    await websocket_send({
                        "type": "error",
                        "message": job.error
                    })

        except Exception as e:
            job.status = "failed"
            job.error = str(e)
            if websocket_send:
                await websocket_send({
                    "type": "error",
                    "message": str(e)
                })

        return job.to_dict()

    def cancel_job(self, job_id: str) -> bool:
        """Cancel a running job"""
        job = self.get_job(job_id)
        if not job:
            return False

        if job.process and job.status == "running":
            job.process.terminate()
            job.status = "cancelled"
            return True

        return False
