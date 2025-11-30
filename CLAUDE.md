# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

PlagDet is a multi-detector plagiarism detection tool with a plugin-based architecture. It orchestrates multiple plagiarism detection engines (JPlag, MOSS, Dolos, CopyDetect) through a unified configuration interface and aggregates their results.

**Architecture:**
- **plagdet/** - Core CLI and detection engine (Python, Typer/Pydantic)
- **backend/** - FastAPI REST API + WebSocket server for real-time progress
- **frontend/** - Next.js 14 web interface with dark theme

**Key Design Principles:**
- Plugin architecture with decorator-based registration
- Pydantic models for all configuration and data validation
- Command-Handler separation in CLI layer
- Service layer for cross-cutting concerns (aggregation, cleanup, output management)
- Factory pattern for plugin instantiation

## Common Commands

### Development Setup
```bash
# Install all dependencies
uv sync --group detectors --group backend --group dev
cd frontend && npm install && cd ..

# Start web interface (frontend + backend)
./scripts/dev.sh

# Kill ports if in use
./scripts/kill-ports.sh
```

### Running Detection
```bash
# CLI: Run with configuration file
uv run plagdet run -c config.yaml

# CLI: Run specific detector(s)
uv run plagdet run -c config.yaml -d jplag -d moss

# Web: Open http://localhost:3000/config to configure and run
```

### Utility Commands
```bash
# List all registered plugins
uv run plagdet list-plugins

# Validate configuration file
uv run plagdet check-config config.yaml

# Clean up detector output files
uv run plagdet cleanup section1/lab1/

# Aggregate results from multiple detectors
uv run plagdet aggregate section1/lab1/ --min-score 70
```

### Development Servers
```bash
# Backend only (from backend/)
cd backend && uv run uvicorn main:app --reload

# Frontend only (from frontend/)
cd frontend && npm run dev

# Code quality
uv run black plagdet/
uv run ruff check plagdet/
cd frontend && npm run lint
```

### Testing
```bash
uv run pytest
```

## Architecture Overview

### Core Components (`plagdet/core/`)

**Plugin System** (`registry.py`):
- Three plugin registries: detectors, outputs, processors
- Decorator-based registration: `@register_detector`, `@register_output`, `@register_processor`
- Plugins auto-register on import in `plagdet/cli/__init__.py`

**Detection Engine** (`engine.py`):
- `PlagiarismDetectionEngine` orchestrates the 6-stage pipeline:
  1. Pre-detection processors (unzip, normalize names)
  2. Run detector(s) - supports multiple detectors
  3. Post-detection processors
  4. Generate outputs (CSV, JSON) via OutputManager
  5. Auto-aggregate results if multiple detectors ran
  6. Cleanup temporary files

**Configuration** (`config.py`, `models/config.py`):
- Pydantic models for type-safe configuration
- `AppConfig` is the root model containing detectors, outputs, processors, and settings

### Plugin Types (`plagdet/plugins/`)

| Type | Base Class | Method | Location |
|------|------------|--------|----------|
| Detectors | `DetectorPlugin` | `detect(target_path, config) -> DetectionResult` | `plugins/detectors/` |
| Outputs | `OutputPlugin` | `write(result, output_path, config)` | `plugins/outputs/` |
| Processors | `ProcessorPlugin` | `process(context, config) -> context` | `plugins/processors/` |

Built-in: JPlag, MOSS, Dolos, CopyDetect (detectors); CSV, JSON (outputs); Unzipper, Normalizer (processors)

### CLI Architecture (`plagdet/cli/`, `plagdet/handlers/`)

- **Commands** (`cli/commands/`): Thin Typer-based definitions delegating to handlers
- **Handlers** (`handlers/`): Business logic layer (RunHandler, PluginHandler, ConfigHandler, etc.)
- **Entry Point** (`cli/__init__.py`): Imports plugins to trigger registration, creates Typer app

### Service Layer (`plagdet/services/`)

- **OutputManager**: Generates multiple output formats from detection results
- **AggregationService**: Combines results from multiple detectors into single CSV
- **CleanupService**: Removes detector-generated files and directories

### Backend API (`backend/`)

FastAPI server providing REST API and WebSocket endpoints:

| Endpoint | Description |
|----------|-------------|
| `GET/PUT /api/config` | Read/write config.yaml |
| `POST /api/config/validate` | Validate config without saving |
| `POST /api/detect` | Start detection job |
| `WS /ws/detect/{job_id}` | WebSocket for real-time progress |
| `GET /api/projects` | List all projects (section*/lab*/) |
| `GET /api/files/compare` | Get two files for diff view |

Services: `ConfigService`, `DetectionService`, `FileService`

### Frontend (`frontend/`)

Next.js 14 App Router with dark theme:

| Route | Description |
|-------|-------------|
| `/` | Dashboard |
| `/config` | Config editor (primary interface) |
| `/reports/[id]` | Report viewer with sortable tables |
| `/compare/[id]` | Side-by-side code diff |

Tech: TypeScript, TailwindCSS, Radix UI, React Hook Form + Zod

## Configuration Structure

```yaml
detectors:
  - name: jplag
    config:
      language: cpp
  - name: moss
    config:
      userid: "YOUR_MOSS_ID"
      language: cc

outputs:
  - name: csv
    config:
      min_score: 70.0
  - name: json
    config:
      pretty: true

settings:
  target_path: ./section1/lab1_cpp/    # Single project
  # target_paths: [./section1/, ./section2/]  # Multiple projects
  auto_aggregate: true
  output_subdir: plagdet_results
```

## Adding New Plugins

### New Detector
1. Create `plagdet/plugins/detectors/my_detector.py`
2. Define config model in `plagdet/plugins/models/detectors.py`
3. Implement:
```python
from plagdet.plugins.base import DetectorPlugin
from plagdet.core.registry import register_detector
from plagdet.core.models.detection import DetectionResult, Comparison

@register_detector
class MyDetector(DetectorPlugin):
    CONFIG_TYPE = MyDetectorConfig  # Optional

    @property
    def name(self) -> str:
        return "my_detector"

    def detect(self, target_path, config) -> DetectionResult:
        comparisons = [Comparison(first="a.py", second="b.py", similarity=85.5)]
        return DetectionResult(comparisons=comparisons, metadata={"detector": self.name})
```
4. Import in `plagdet/cli/__init__.py` to register
5. Add config mapping to `PlagiarismDetectionEngine.DETECTOR_CONFIG_MAP`

### New Output/Processor
Same pattern: create file, define config model, implement class with decorator, import in CLI.

## External Dependencies

- **JPlag**: Java runtime + `jplag.jar` in project root
- **MOSS**: `mosspy` package + MOSS user ID from moss.stanford.edu
- **Dolos**: Node.js + `npm install -g @dodona/dolos`
- **CopyDetect**: `copydetect` Python package (installed with `--group detectors`)

## Output Naming Convention

- Individual detector: `{target_dirname}_{detector}.{csv|json}` (e.g., `lab1_cpp_jplag.csv`)
- Aggregated: `aggregated.csv`
- Unique names: `unique_names.csv`
- Results directory: `{target_path}/plagdet_results/`

## Important URLs (when running ./scripts/dev.sh)

- Frontend: http://localhost:3000
- Backend API: http://localhost:8000
- API Docs: http://localhost:8000/docs
- Config Editor: http://localhost:3000/config
