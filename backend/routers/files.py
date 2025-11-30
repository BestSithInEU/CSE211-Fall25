"""
Files router - handles source code file access
"""

from fastapi import APIRouter, HTTPException, Query

from services.file_service import FileService
from models.api_models import FileResponse, CompareResponse


router = APIRouter()
file_service = FileService()


@router.get("/files/{project_id:path}/{filename:path}", response_model=FileResponse)
async def get_file(project_id: str, filename: str):
    """Get source code file content"""
    try:
        relative_path = f"{project_id}/{filename}"
        content = file_service.read_file(relative_path)
        language = file_service.detect_language(filename)

        return FileResponse(
            content=content,
            language=language,
            filename=filename
        )

    except FileNotFoundError as e:
        raise HTTPException(status_code=404, detail=str(e))
    except ValueError as e:
        raise HTTPException(status_code=403, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/files/compare", response_model=CompareResponse)
async def compare_files(
    project: str = Query(..., description="Project path (e.g., section1/lab1_cpp)"),
    file1: str = Query(..., description="First file name"),
    file2: str = Query(..., description="Second file name")
):
    """Get two files for side-by-side comparison"""
    try:
        content1, content2 = file_service.read_comparison_files(project, file1, file2)
        language = file_service.detect_language(file1)

        return CompareResponse(
            file1=file1,
            file2=file2,
            content1=content1,
            content2=content2,
            language=language
        )

    except FileNotFoundError as e:
        raise HTTPException(status_code=404, detail=str(e))
    except ValueError as e:
        raise HTTPException(status_code=403, detail=str(e))
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
