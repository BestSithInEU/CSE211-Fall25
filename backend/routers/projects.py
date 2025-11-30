"""
Projects router - handles project and report discovery
"""

import json
import csv
from pathlib import Path
from fastapi import APIRouter, HTTPException, Query
from typing import List, Dict, Any

from services.config_service import ConfigService
from models.api_models import ProjectResponse


router = APIRouter()
config_service = ConfigService()


def get_output_subdir() -> str:
    """Get the output subdirectory name from config."""
    try:
        config = config_service.get_config()
        return config.settings.output_subdir
    except Exception:
        # Fallback to PlagDet's default
        return "results"


def discover_projects() -> List[Dict[str, Any]]:
    """
    Discover all projects (section*/lab*/) with plagdet results
    """
    # Backend runs from backend/ directory, so look in parent (project root)
    base_dir = Path(__file__).parent.parent.parent
    projects = []

    # Get output_subdir from config (defaults to "results" in PlagDet)
    output_subdir = get_output_subdir()

    # Find all section*/lab*/ directories
    for section_dir in base_dir.glob("section*"):
        if not section_dir.is_dir():
            continue

        for lab_dir in section_dir.glob("lab*"):
            if not lab_dir.is_dir():
                continue

            # Check if results directory exists
            results_dir = lab_dir / output_subdir
            if not results_dir.exists():
                continue

            # Find all reports in results directory
            reports = []
            detectors_run = set()
            highest_sim = 0.0

            for report_file in results_dir.glob("*"):
                if report_file.suffix in ['.csv', '.json']:
                    reports.append(report_file.name)

                    # Extract detector name
                    if '_' in report_file.stem:
                        detector = report_file.stem.split('_')[-1]
                        detectors_run.add(detector)

                    # Get highest similarity from CSV if available
                    if report_file.suffix == '.csv' and 'aggregated' not in report_file.name:
                        try:
                            with open(report_file, 'r') as f:
                                reader = csv.DictReader(f)
                                for row in reader:
                                    sim = float(row.get('Similarity', row.get('Average', 0)))
                                    highest_sim = max(highest_sim, sim)
                        except Exception:
                            pass

            project_id = f"{section_dir.name}/{lab_dir.name}"
            projects.append({
                "id": project_id,
                "name": lab_dir.name,
                "path": str(lab_dir),
                "reports": reports,
                "detectors_run": list(detectors_run),
                "highest_similarity": highest_sim if highest_sim > 0 else None,
                "last_run": None  # Could add by checking file modification time
            })

    return projects


@router.get("/projects", response_model=List[ProjectResponse])
async def list_projects():
    """List all discovered projects"""
    try:
        projects = discover_projects()
        return projects
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/project-reports")
async def get_project_reports(project_id: str = Query(..., description="Project ID (e.g., section1/lab1_cpp)")):
    """Get all reports for a project"""
    try:
        # Get project
        projects = discover_projects()
        project = next((p for p in projects if p["id"] == project_id), None)

        if not project:
            raise HTTPException(status_code=404, detail=f"Project not found: {project_id}")

        # Read all report files
        output_subdir = get_output_subdir()
        results_dir = Path(project["path"]) / output_subdir
        reports_data = []

        for report_name in project["reports"]:
            report_path = results_dir / report_name

            if report_path.suffix == '.json':
                with open(report_path, 'r') as f:
                    data = json.load(f)
                    reports_data.append({
                        "filename": report_name,
                        "format": "json",
                        "data": data
                    })

            elif report_path.suffix == '.csv':
                with open(report_path, 'r') as f:
                    reader = csv.DictReader(f)
                    rows = list(reader)
                    reports_data.append({
                        "filename": report_name,
                        "format": "csv",
                        "data": {
                            "columns": reader.fieldnames,
                            "rows": rows
                        }
                    })

        return {"reports": reports_data}

    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/projects/{project_id:path}")
async def get_project(project_id: str):
    """Get detailed project information"""
    try:
        projects = discover_projects()
        project = next((p for p in projects if p["id"] == project_id), None)

        if not project:
            raise HTTPException(status_code=404, detail=f"Project not found: {project_id}")

        return project

    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))


@router.get("/reports/{report_id}")
async def get_report(report_id: str):
    """Get specific report by ID (format: project_id/report_filename)"""
    try:
        # Parse report_id (e.g., "section1/lab1/lab1_jplag.csv")
        parts = report_id.split('/')
        if len(parts) < 3:
            raise HTTPException(status_code=400, detail="Invalid report ID format")

        project_path = '/'.join(parts[:-1])
        report_filename = parts[-1]

        output_subdir = get_output_subdir()
        report_path = Path(project_path) / output_subdir / report_filename

        if not report_path.exists():
            raise HTTPException(status_code=404, detail=f"Report not found: {report_id}")

        if report_path.suffix == '.json':
            with open(report_path, 'r') as f:
                return json.load(f)

        elif report_path.suffix == '.csv':
            with open(report_path, 'r') as f:
                reader = csv.DictReader(f)
                return {
                    "columns": reader.fieldnames,
                    "rows": list(reader)
                }

        else:
            raise HTTPException(status_code=400, detail="Unsupported report format")

    except HTTPException:
        raise
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
