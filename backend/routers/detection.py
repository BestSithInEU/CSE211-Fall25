"""
Detection router - handles plagiarism detection execution
"""

import json
from fastapi import APIRouter, WebSocket, WebSocketDisconnect, HTTPException
from typing import Optional, List

from services.detection_service import DetectionService
from models.api_models import DetectionRequest, DetectionJobResponse


router = APIRouter()
detection_service = DetectionService()


@router.post("/detect", response_model=DetectionJobResponse)
async def start_detection(request: DetectionRequest):
    """Start a new plagiarism detection job"""
    try:
        config_path = request.config_path or "config.yaml"
        job_id = detection_service.create_job(
            config_path=config_path,
            detectors=request.detectors,
            verbose=request.verbose
        )

        return DetectionJobResponse(
            job_id=job_id,
            status="pending",
            message=f"Detection job created with ID: {job_id}. Connect to WebSocket at /ws/detect/{job_id}"
        )

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.websocket("/ws/detect/{job_id}")
async def detection_websocket(websocket: WebSocket, job_id: str):
    """WebSocket endpoint for real-time detection progress"""
    await websocket.accept()

    job = detection_service.get_job(job_id)
    if not job:
        await websocket.send_json({
            "type": "error",
            "message": f"Job not found: {job_id}"
        })
        await websocket.close()
        return

    async def send_message(data: dict):
        """Helper to send WebSocket messages"""
        try:
            await websocket.send_json(data)
        except Exception:
            pass  # Client disconnected

    try:
        # Start detection
        result = await detection_service.run_detection(job_id, send_message)

        # Send final status
        await websocket.send_json({
            "type": "complete",
            "result": result
        })

    except WebSocketDisconnect:
        # Client disconnected, but job continues
        pass
    except Exception as e:
        await websocket.send_json({
            "type": "error",
            "message": str(e)
        })
    finally:
        await websocket.close()


@router.get("/detect/{job_id}")
async def get_job_status(job_id: str):
    """Get status of a detection job"""
    job = detection_service.get_job(job_id)
    if not job:
        raise HTTPException(status_code=404, detail=f"Job not found: {job_id}")

    return job.to_dict()


@router.delete("/detect/{job_id}")
async def cancel_job(job_id: str):
    """Cancel a running detection job"""
    success = detection_service.cancel_job(job_id)
    if not success:
        raise HTTPException(
            status_code=400,
            detail=f"Could not cancel job: {job_id}"
        )

    return {"message": f"Job {job_id} cancelled successfully"}
