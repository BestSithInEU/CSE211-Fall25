# PlagDet Backend API

FastAPI backend providing REST API and WebSocket endpoints for the PlagDet Next.js frontend.

## Features

- 🔌 **RESTful API** - Standard HTTP endpoints for config, projects, files
- ⚡ **WebSocket Support** - Real-time detection progress streaming
- 📝 **Auto-generated Docs** - Interactive API documentation at `/docs`
- 🔒 **Path Security** - Path traversal protection for file access
- ✅ **Type Safety** - Pydantic models for validation
- 🔄 **PlagDet Integration** - Direct import of PlagDet core modules

## Tech Stack

- **Framework**: FastAPI 0.109.0
- **Server**: Uvicorn 0.27.0 (ASGI)
- **Validation**: Pydantic 2.5.0 (shared with PlagDet)
- **YAML**: PyYAML 6.0.1 (shared with PlagDet)
- **WebSockets**: websockets 12.0
- **Async I/O**: aiofiles 23.2.1

## Setup

### Prerequisites

- Python 3.9+
- uv (modern Python package manager)
- PlagDet installed (parent directory)

### Installation

```bash
# Install backend dependencies using uv
cd ../  # Go to project root
uv sync --group backend

# This installs:
# - PlagDet and its dependencies
# - FastAPI and backend-specific packages
```

### Running the Server

```bash
# From backend directory
cd backend

# Development mode (with auto-reload)
uv run uvicorn main:app --reload --host 0.0.0.0 --port 8000

# Production mode
uv run uvicorn main:app --host 0.0.0.0 --port 8000 --workers 4

# Or run via Python module
uv run python main.py
```

The API will be available at:
- **API**: http://localhost:8000
- **Docs**: http://localhost:8000/docs (Swagger UI)
- **ReDoc**: http://localhost:8000/redoc (Alternative docs)

### Quick Start with Script

```bash
# From project root, run both frontend + backend
./scripts/dev.sh
```

## Project Structure

```
backend/
├── main.py                   # FastAPI app entry point
├── routers/                  # API route handlers
│   ├── config.py            # Config CRUD + validation
│   ├── detection.py         # Detection execution + WebSocket
│   ├── projects.py          # Project discovery
│   └── files.py             # Source file access
├── services/                 # Business logic
│   ├── config_service.py    # Config read/write/validate
│   ├── detection_service.py # CLI execution, job management
│   └── file_service.py      # Safe file access
├── models/                   # Pydantic models
│   └── api_models.py        # Request/response schemas
└── README.md                # This file
```

## API Endpoints

### Config Management

```
GET  /api/config              # Read config.yaml
PUT  /api/config              # Save config.yaml
POST /api/config/validate     # Validate config without saving
GET  /api/config/schema       # Get JSON Schema for forms
GET  /api/detectors           # List available detector plugins
GET  /api/outputs             # List available output plugins
```

### Detection

```
POST /api/detect              # Start detection job
WS   /ws/detect/{job_id}      # WebSocket for real-time progress
GET  /api/detect/{job_id}     # Get job status
DELETE /api/detect/{job_id}   # Cancel running job
```

### Projects & Reports

```
GET  /api/projects            # List all projects (section*/lab*/)
GET  /api/projects/{id}       # Get project details
GET  /api/projects/{id}/reports  # Get all reports for project
GET  /api/reports/{id}        # Get specific report data
```

### File Access

```
GET  /api/files/{project_id}/{filename}  # Get source file content
GET  /api/files/compare       # Get two files for diff
    ?project=...&file1=...&file2=...
```

### Health Check

```
GET  /                        # API info
GET  /health                  # Health check
```

## Services

### ConfigService
**Responsibilities**: Config YAML operations

- Reads/writes `config.yaml`
- Validates using PlagDet's `AppConfig` Pydantic model
- Provides JSON Schema for frontend forms
- Extracts target paths from config

**Example**:
```python
from services.config_service import ConfigService

service = ConfigService()
config = service.read_validated()  # Returns AppConfig
is_valid, errors = service.validate(config_dict)
```

### DetectionService
**Responsibilities**: Run PlagDet CLI, manage jobs

- Creates unique job IDs (UUID)
- Spawns subprocess: `uv run plagdet run -c config.yaml`
- Streams stdout/stderr to WebSocket clients
- Handles job cancellation

**Example**:
```python
from services.detection_service import DetectionService

service = DetectionService()
job_id = service.create_job("config.yaml", ["jplag", "moss"])
await service.run_detection(job_id, websocket_send)
```

### FileService
**Responsibilities**: Safe file system access

- Path traversal protection (validates all paths)
- 1MB file size limit
- Auto-detects programming language from extension
- Read-only access to source files

**Example**:
```python
from services.file_service import FileService

service = FileService()
content = service.read_file("section1/lab1/student1.cpp")
content1, content2 = service.read_comparison_files(
    "section1/lab1", "student1.cpp", "student2.cpp"
)
```

## Security

### Path Traversal Protection
All file paths are validated using `Path.resolve()`:
```python
# ✅ Allowed
/api/files/section1/lab1/student1.cpp

# ❌ Blocked (path traversal)
/api/files/../../etc/passwd
/api/files/../config.yaml
```

### CORS Policy
Restricted to frontend origin:
```python
allow_origins=["http://localhost:3000"]
```

### Input Validation
All request bodies validated by Pydantic models:
```python
@router.post("/api/detect")
async def start_detection(request: DetectionRequest):
    # request is validated automatically
```

## WebSocket Protocol

### Detection Progress Stream

**Connect**: `ws://localhost:8000/ws/detect/{job_id}`

**Message Types**:
```json
// Status update
{"type": "status", "status": "running", "message": "Starting detection..."}

// CLI output
{"type": "output", "message": "Processing file: student1.cpp"}

// Completion
{"type": "complete", "result": {...}}

// Error
{"type": "error", "message": "Detection failed: ..."}
```

**Client Example**:
```javascript
const ws = new WebSocket(`ws://localhost:8000/ws/detect/${jobId}`)

ws.onmessage = (event) => {
  const data = JSON.parse(event.data)
  if (data.type === 'output') {
    console.log(data.message)
  }
}
```

## Development

### Testing API Endpoints

**Using curl**:
```bash
# Get config
curl http://localhost:8000/api/config

# Validate config
curl -X POST http://localhost:8000/api/config/validate \
  -H "Content-Type: application/json" \
  -d @config.json

# Start detection
curl -X POST http://localhost:8000/api/detect \
  -H "Content-Type: application/json" \
  -d '{"config_path": "config.yaml", "verbose": true}'
```

**Using Swagger UI**:
1. Open http://localhost:8000/docs
2. Expand endpoint
3. Click "Try it out"
4. Fill in parameters
5. Click "Execute"

### Adding New Endpoints

1. Create router in `routers/` directory
2. Define Pydantic models in `models/api_models.py`
3. Implement business logic in `services/`
4. Register router in `main.py`:

```python
from routers import my_router

app.include_router(my_router.router, prefix="/api", tags=["my_feature"])
```

### Error Handling

FastAPI automatically converts exceptions to HTTP errors:

```python
from fastapi import HTTPException

@router.get("/api/something")
async def get_something():
    if not exists:
        raise HTTPException(status_code=404, detail="Not found")
    return data
```

## Environment Variables

Backend reads from environment:

```bash
# Optional: Override config file path
export PLAGDET_CONFIG=config.yaml

# Optional: Change server host/port
uvicorn main:app --host 0.0.0.0 --port 8080
```

## Deployment

### Production Setup

```bash
# Install production dependencies
uv sync --group backend --no-dev

# Run with multiple workers
uv run uvicorn main:app \
  --host 0.0.0.0 \
  --port 8000 \
  --workers 4 \
  --no-access-log
```

### Docker (Optional)

```dockerfile
FROM python:3.11-slim

WORKDIR /app

# Install uv
COPY --from=ghcr.io/astral-sh/uv:latest /uv /usr/local/bin/uv

# Copy project files
COPY pyproject.toml .
COPY plagdet/ plagdet/
COPY backend/ backend/

# Install dependencies
RUN uv sync --group backend

# Run server
CMD ["uv", "run", "uvicorn", "backend.main:app", "--host", "0.0.0.0", "--port", "8000"]
```

### Nginx Reverse Proxy

```nginx
server {
    listen 80;
    server_name plagdet.example.com;

    location / {
        proxy_pass http://localhost:3000;  # Next.js frontend
    }

    location /api/ {
        proxy_pass http://localhost:8000;  # FastAPI backend
        proxy_set_header Host $host;
        proxy_set_header X-Real-IP $remote_addr;
    }

    location /ws/ {
        proxy_pass http://localhost:8000;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "upgrade";
    }
}
```

## Troubleshooting

### Import Errors (PlagDet modules not found)

```bash
# Ensure running from backend/ directory
cd backend
uv run python main.py

# Or set PYTHONPATH
export PYTHONPATH=/path/to/CSE211-Fall25:$PYTHONPATH
```

### Port Already in Use

```bash
# Find process using port 8000
lsof -i :8000

# Kill process
kill -9 <PID>

# Or use different port
uv run uvicorn main:app --port 8001
```

### WebSocket Connection Failed

- Check firewall settings
- Verify frontend is using correct WS URL
- Test with wscat: `wscat -c ws://localhost:8000/ws/detect/test-id`

### CORS Errors

Add frontend origin to `main.py`:
```python
app.add_middleware(
    CORSMiddleware,
    allow_origins=["http://localhost:3000", "https://your-domain.com"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
```

## Dependencies

Backend dependencies are managed in root `pyproject.toml`:

```toml
[dependency-groups]
backend = [
    "fastapi>=0.109.0",
    "uvicorn[standard]>=0.27.0",
    "python-multipart>=0.0.6",
    "websockets>=12.0",
    "aiofiles>=23.2.1",
]
```

Install with:
```bash
uv sync --group backend
```

## Contributing

1. Follow FastAPI best practices
2. Add type hints to all functions
3. Document endpoints with docstrings
4. Add Pydantic models for request/response
5. Include examples in docstrings
6. Test endpoints with Swagger UI

## License

Part of PlagDet project - see root LICENSE file.
