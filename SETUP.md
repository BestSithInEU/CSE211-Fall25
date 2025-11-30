# PlagDet Setup Guide

Complete setup guide for PlagDet plagiarism detection tool with web interface.

## Prerequisites

### Required
- **Python 3.9+** - [Download](https://www.python.org/downloads/)
- **uv** - Modern Python package manager
  ```bash
  curl -LsSf https://astral.sh/uv/install.sh | sh
  ```
- **Node.js 20+** - [Download](https://nodejs.org/)
- **npm** - Comes with Node.js

### Optional (Detector-Specific)
- **Java** - Required for JPlag detector
- **MOSS User ID** - [Register via email](mailto:moss@moss.stanford.edu)
- **Dolos** - Install via npm: `npm install -g @dodona/dolos`

## Installation Steps

### 1. Clone/Navigate to Project

```bash
cd /path/to/CSE211-Fall25
```

### 2. Install Python Dependencies

```bash
# Install core PlagDet
uv sync

# Install detector dependencies (MOSS, CopyDetect)
uv sync --group detectors

# Install backend dependencies (FastAPI, WebSockets)
uv sync --group backend
```

### 3. Install Frontend Dependencies

```bash
cd frontend
npm install
cd ..
```

### 4. Verify Installation

```bash
# Test PlagDet CLI
uv run plagdet --help

# Test backend can import plagdet
cd backend
uv run python -c "from plagdet.core.config import AppConfig; print('✓ Backend can import PlagDet')"
cd ..
```

## Configuration

### 1. Create/Edit config.yaml

You can use the example config or create your own:

```bash
cp jplag_config.example.yaml config.yaml
# Edit config.yaml with your settings
```

Or use the web interface (recommended):
```bash
./scripts/dev.sh
# Open http://localhost:3000/config
```

### 2. Set Up Detector Requirements

#### JPlag (Recommended)
```bash
# Download JPlag JAR
wget https://github.com/jplag/JPlag/releases/latest/download/jplag.jar

# Place in project root
mv jplag.jar ./
```

#### MOSS (Optional)
1. Email `moss@moss.stanford.edu` with body:
   ```
   registeruser
   mail your.email@university.edu
   ```
2. Wait for reply with user ID
3. Update `config.yaml`:
   ```yaml
   detectors:
     - name: moss
       config:
         userid: "YOUR_MOSS_ID_HERE"
         language: cc
   ```

#### Dolos (Optional)
```bash
npm install -g @dodona/dolos
```

#### CopyDetect (Already installed with --group detectors)
No additional setup needed!

## Configuration (Optional)

Create a `.env` file to customize ports and settings:

```bash
# Copy example configuration
cp .env.example .env

# Edit with your preferences
nano .env
```

Available options:
```bash
BACKEND_HOST=0.0.0.0          # Backend bind address
BACKEND_PORT=8000             # Backend port
FRONTEND_PORT=3000            # Frontend port
FRONTEND_URL=http://localhost:3000  # CORS origin
NEXT_PUBLIC_API_URL=http://localhost:8000  # Frontend API endpoint
```

## Running PlagDet

### Option 1: Web Interface (Recommended)

Start both frontend and backend:

```bash
./scripts/dev.sh
```

The script will:
- ✅ Check if ports are available
- ✅ Auto-install frontend dependencies if missing
- ✅ Wait for servers to start properly
- ✅ Create log files (`backend.log`, `frontend.log`)
- ✅ Handle graceful shutdown

Then open your browser:
- **Frontend**: http://localhost:3000 (or your custom port)
- **Backend API**: http://localhost:8000 (or your custom port)
- **API Docs**: http://localhost:8000/docs

**Workflow:**
1. Navigate to Config Editor (`/config`)
2. Set target path (e.g., `./section1/lab1_cpp/`)
3. Select detectors (check JPlag, MOSS, etc.)
4. Adjust similarity threshold
5. Click "Run Detection"
6. View results in Reports page

### Option 2: Command Line

```bash
# Run detection
uv run plagdet run -c config.yaml

# Run with specific detectors
uv run plagdet run -c config.yaml -d jplag -d moss

# View results
ls section1/lab1_cpp/plagdet_results/
```

## Testing Your Setup

### Test with Sample Data

```bash
# The project includes sample C++ files in section1/lab1_cpp/
ls section1/lab1_cpp/

# Run detection on sample data
uv run plagdet run -c config.yaml

# Check results
ls section1/lab1_cpp/plagdet_results/
```

### Web Interface Test

```bash
# Start servers
./scripts/dev.sh

# In browser (http://localhost:3000):
# 1. Go to Config Editor
# 2. Set target_path: ./section1/lab1_cpp/
# 3. Enable JPlag detector
# 4. Click "Run Detection"
# 5. Navigate to Reports to view results
```

## Project Structure

```
CSE211-Fall25/
├── plagdet/                  # Core plagiarism detection engine
│   ├── cli/                 # Command-line interface
│   ├── core/                # Core logic, config, registry
│   ├── plugins/             # Detector/output/processor plugins
│   ├── services/            # Aggregation, cleanup services
│   └── ui/                  # CLI formatting
│
├── frontend/                 # Next.js web interface
│   ├── app/                 # Pages: dashboard, config, reports
│   ├── components/          # React components
│   ├── lib/                 # API client, types, utils
│   └── package.json
│
├── backend/                  # FastAPI backend
│   ├── main.py              # API entry point
│   ├── routers/             # API endpoints
│   ├── services/            # Business logic
│   └── models/              # Pydantic schemas
│
├── scripts/
│   └── dev.sh               # Start both servers
│
├── config.yaml              # Main configuration file
├── pyproject.toml           # Python dependencies (uv)
└── README.md                # Project documentation
```

## Dependency Management

### Python Dependencies (uv)

All Python dependencies are managed in `pyproject.toml`:

```toml
[project]
dependencies = [
    "pydantic>=2.0.0",
    "pyyaml>=6.0",
    # ... core dependencies
]

[dependency-groups]
detectors = [
    "mosspy>=1.0.0",
    "copydetect>=0.5.0",
]
backend = [
    "fastapi>=0.109.0",
    "uvicorn[standard]>=0.27.0",
    "websockets>=12.0",
]
```

**Commands:**
```bash
# Install everything
uv sync --group detectors --group backend

# Add new dependency
uv add package-name

# Add to specific group
uv add --group backend new-package
```

### Frontend Dependencies (npm)

Managed in `frontend/package.json`:

```bash
cd frontend

# Add dependency
npm install package-name

# Add dev dependency
npm install -D package-name

# Update all packages
npm update
```

## Troubleshooting

### Backend can't import plagdet

**Problem**: `ModuleNotFoundError: No module named 'plagdet'`

**Solution**:
```bash
# Ensure running from backend/ directory
cd backend
uv run python main.py

# Or add parent to PYTHONPATH
export PYTHONPATH=/path/to/CSE211-Fall25:$PYTHONPATH
```

### Port already in use

**Problem**: `Error: Port 8000 or 3000 already in use`

**Solution 1: Use helper script** (recommended):
```bash
# Kill processes on both ports
./scripts/kill-ports.sh

# Kill backend only
./scripts/kill-ports.sh backend

# Kill frontend only
./scripts/kill-ports.sh frontend
```

**Solution 2: Manual**:
```bash
# Find and kill process on port 8000
lsof -ti:8000 | xargs kill -9

# Find and kill process on port 3000
lsof -ti:3000 | xargs kill -9
```

**Solution 3: Use different ports**:
```bash
# Create .env file
cat > .env << EOF
BACKEND_PORT=8001
FRONTEND_PORT=3001
EOF

# Run with custom ports
./scripts/dev.sh
```

### Viewing Logs

**Problem**: Need to see detailed server output

**Solution**:
```bash
# View backend logs
tail -f backend.log

# View frontend logs
tail -f frontend.log

# View both in split terminal
# Terminal 1:
tail -f backend.log

# Terminal 2:
tail -f frontend.log
```

### Frontend dependencies not found

**Problem**: `next: command not found`

**Solution**:
```bash
# Install frontend dependencies
cd frontend
npm install
cd ..

# Re-run dev script (it will check automatically)
./scripts/dev.sh
```

### Frontend can't connect to backend

**Problem**: API calls fail with network error

**Solution**:
1. Verify backend is running: `curl http://localhost:8000/health`
2. Check backend logs: `tail -f backend.log`
3. Verify ports in `.env` match
4. Check CORS settings in `backend/main.py`
5. Ensure `NEXT_PUBLIC_API_URL` in `.env` points to correct backend

### WebSocket connection failed

**Problem**: Real-time progress doesn't work

**Solution**:
1. Check firewall settings
2. Try polling fallback: `GET /api/detect/{job_id}`
3. Verify WS URL: `ws://localhost:8000/ws/detect/{id}`

### JPlag not found

**Problem**: `jplag.jar not found`

**Solution**:
```bash
# Download JPlag
wget https://github.com/jplag/JPlag/releases/latest/download/jplag.jar

# Place in project root
mv jplag.jar /path/to/CSE211-Fall25/
```

### MOSS detector fails

**Problem**: `MOSS user ID is invalid`

**Solution**:
1. Register for MOSS ID (see setup above)
2. Update `config.yaml` with correct user ID
3. Test connection: `uv run plagdet run -c config.yaml -d moss --verbose`

## Development

### Running Individual Components

**Backend only:**
```bash
cd backend
uv run uvicorn main:app --reload
```

**Frontend only:**
```bash
cd frontend
npm run dev
```

**PlagDet CLI only:**
```bash
uv run plagdet run -c config.yaml
```

### Code Quality

```bash
# Format Python code
uv run black plagdet/

# Lint Python code
uv run ruff check plagdet/

# Format frontend code
cd frontend
npm run lint
npm run format
```

### Adding New Features

See development guides:
- **Frontend**: `frontend/README.md`
- **Backend**: `backend/README.md`
- **PlagDet Core**: `README.md`

## Next Steps

1. **Run sample detection** to verify everything works
2. **Explore web interface** at http://localhost:3000
3. **Configure for your use case** in Config Editor
4. **Read detector documentation** for specific setup requirements
5. **Check API docs** at http://localhost:8000/docs

## Getting Help

- **Issues**: Report bugs at repository issues page
- **Documentation**:
  - Design doc: `docs/plans/2025-11-20-nextjs-frontend-design.md`
  - Project README: `README.md`
  - Frontend README: `frontend/README.md`
  - Backend README: `backend/README.md`
- **API Reference**: http://localhost:8000/docs (when server is running)

## Quick Reference

### Common Commands

```bash
# Start everything
./scripts/dev.sh

# Kill ports if in use
./scripts/kill-ports.sh

# View logs
tail -f backend.log
tail -f frontend.log

# Run detection (CLI)
uv run plagdet run -c config.yaml

# List plugins
uv run plagdet list-plugins

# Cleanup results
uv run plagdet cleanup section1/lab1/

# Aggregate results
uv run plagdet aggregate section1/lab1/

# Install dependencies
uv sync --group detectors --group backend
cd frontend && npm install

# Configure custom ports
cp .env.example .env
# Edit .env with your ports
./scripts/dev.sh
```

### Important URLs

- Frontend: http://localhost:3000
- Backend: http://localhost:8000
- API Docs: http://localhost:8000/docs
- Config Editor: http://localhost:3000/config
- Reports: http://localhost:3000/reports

### File Locations

- Config: `./config.yaml`
- Results: `section*/lab*/plagdet_results/`
- Frontend: `./frontend/`
- Backend: `./backend/`
- Core: `./plagdet/`
