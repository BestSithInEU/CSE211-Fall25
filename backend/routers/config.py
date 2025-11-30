"""
Config router - handles config.yaml operations
"""

from fastapi import APIRouter, HTTPException
from typing import Dict, Any

from services.config_service import ConfigService
from models.api_models import ValidationResponse, ErrorResponse


router = APIRouter()
config_service = ConfigService()


@router.get("/config")
async def get_config() -> Dict[str, Any]:
    """Get current config.yaml contents"""
    try:
        return config_service.read()
    except FileNotFoundError as e:
        raise HTTPException(status_code=404, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.put("/config")
async def save_config(config: Dict[str, Any]) -> Dict[str, str]:
    """Save config.yaml"""
    try:
        # Validate before saving
        is_valid, errors = config_service.validate(config)
        if not is_valid:
            raise HTTPException(
                status_code=400,
                detail="Invalid configuration",
                headers={"errors": str(errors)}
            )

        config_service.write(config)
        return {"message": "Configuration saved successfully"}

    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.post("/config/validate")
async def validate_config(config: Dict[str, Any]) -> ValidationResponse:
    """Validate config without saving"""
    try:
        is_valid, errors = config_service.validate(config)

        if is_valid:
            return ValidationResponse(
                valid=True,
                message="Configuration is valid"
            )
        else:
            return ValidationResponse(
                valid=False,
                errors=errors,
                message="Configuration has validation errors"
            )

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/config/schema")
async def get_config_schema() -> Dict[str, Any]:
    """Get JSON schema for config validation"""
    try:
        return config_service.get_schema()
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/detectors")
async def list_detectors():
    """List available detector plugins"""
    try:
        from plagdet.core.registry import detector_registry

        detectors = []
        for name, detector_class in detector_registry.items():
            detector_instance = detector_class()
            detectors.append({
                "name": name,
                "description": detector_instance.__doc__ or f"{name} detector",
                "config_type": getattr(detector_instance, 'CONFIG_TYPE', None).__name__
                if hasattr(detector_instance, 'CONFIG_TYPE') else None
            })

        return {"detectors": detectors}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/outputs")
async def list_outputs():
    """List available output plugins"""
    try:
        from plagdet.core.registry import output_registry

        outputs = []
        for name, output_class in output_registry.items():
            output_instance = output_class()
            outputs.append({
                "name": name,
                "description": output_instance.__doc__ or f"{name} output",
                "config_type": getattr(output_instance, 'CONFIG_TYPE', None).__name__
                if hasattr(output_instance, 'CONFIG_TYPE') else None
            })

        return {"outputs": outputs}

    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
