# PlagDet

A configurable, plugin-based plagiarism detection tool for student submissions with a modern web interface.

## Features

- **Plugin Architecture**: Extensible system supporting multiple detection tools, output formats, and processors
- **YAML Configuration**: Easy-to-use configuration files for managing detection pipelines
- **Multiple Outputs**: Generate CSV, JSON, or custom output formats simultaneously
- **Pipeline Processors**: Pre and post-detection processing for submission preparation and result normalization
- **Built-in Plugins**:
  - **Detectors**: JPlag, MOSS, Dolos, CopyDetect
  - **Outputs**: CSV, JSON
  - **Processors**: Unzipper, Name Normalizer

## Installation

```bash
# Using uv (recommended)
uv sync

# Install optional detector dependencies
uv sync --group detectors

# Install backend dependencies for web interface
uv sync --group backend

# Or using pip
pip install -e .
pip install -e ".[detectors]"  # For MOSS, CopyDetect, and Dolos support
```

## Web Interface (Recommended)

PlagDet now includes a modern web interface for easy configuration and result viewing!

### Quick Start with Web UI

```bash
# Install dependencies
uv sync --group backend
cd frontend && npm install && cd ..

# Start both frontend and backend
./scripts/dev.sh
```

Then open http://localhost:3000 in your browser.

**Features:**
- 📝 **Visual Config Editor** - No YAML editing required
- ▶️ **One-Click Detection** - Run plagiarism detection from the UI
- 📊 **Interactive Reports** - Sortable tables, color-coded similarity scores
- 🔍 **Code Comparison** - Side-by-side diff viewer
- ⚡ **Real-Time Progress** - Live updates during detection

See `frontend/README.md` and `backend/README.md` for detailed documentation.

## Command Line Interface

### Quick Start

1. Create a configuration file (see `jplag_config.example.yaml`):

```yaml
detector:
  name: jplag
  config:
    language: python3
    token_length: 10

outputs:
  - name: csv
    config:
      min_score: 80.0
      metric: AVG

settings:
  target_path: ./submissions/
  verbose: true
```

2. Run plagiarism detection:

```bash
uv run plagdet run --config config.yaml
```

## CLI Usage

### Run Detection

```bash
uv run plagdet run --config config.yaml [--verbose]
```

### List Available Plugins

```bash
uv run plagdet list-plugins
```

### Unzip Submissions

```bash
uv run plagdet unzip submissions.zip ./output/
```

### Cleanup Results

```bash
# Clean default directory (section1/lab1_cpp/)
uv run plagdet cleanup

# Clean specific directory
uv run plagdet cleanup section1/lab1/

# Clean all test directories
uv run plagdet cleanup --all
```

### Aggregate Results from Multiple Detectors

After running multiple detectors on the same dataset, combine results into a single CSV:

```bash
# Aggregate all detector results
uv run plagdet aggregate section1/lab1/

# Specify output file
uv run plagdet aggregate section1/lab1/ --output combined_results.csv

# Filter by minimum similarity score
uv run plagdet aggregate section1/lab1/ --min-score 70
```

**Output Format:**
```csv
First Submission,Second Submission,JPLAG,MOSS,DOLOS,COPYDETECT,Average,Count
student1.py,student2.py,87.20,85.50,84.30,86.00,85.75,4
student1.py,student3.py,92.30,-,-,91.50,91.90,2
```

The aggregated CSV includes:
- Each detector's similarity score (or "-" if not detected)
- Average score across all detectors
- Count of detectors that found the pair

## Configuration

See `jplag_config.example.yaml` for a complete configuration example with all available options.

### Detector Configuration

Specify which plagiarism detection tool to use:

```yaml
detector:
  name: jplag
  config:
    language: python3      # Programming language
    token_length: 10       # Minimum token match length
    base_path: null        # Optional base code path
```

### Output Configuration

Generate multiple output formats:

```yaml
outputs:
  - name: csv
    config:
      min_score: 80.0
      metric: AVG
      include_unique_names: true

  - name: json
    config:
      pretty: true
      min_score: 80.0
```

### Pipeline Processors

Add pre/post-processing steps:

```yaml
processors:
  pre_detection:
    - name: unzipper
      config:
        zip_file: submissions.zip
        extract_to: ./submissions/

  post_detection:
    - name: normalizer
      config:
        strategy: turkish
```

## Extending with Plugins

### Creating a New Detector

```python
from plagdet.plugins.base import DetectorPlugin
from plagdet.core.models.detection import DetectionResult, Comparison
from plagdet.core.registry import register_detector

@register_detector
class MyDetector(DetectorPlugin):
    @property
    def name(self) -> str:
        return "my_detector"

    def detect(self, target_path: str, config) -> DetectionResult:
        # Your detection logic here
        comparisons = [
            Comparison(
                first_submission="student1.py",
                second_submission="student2.py",
                similarity=0.85
            )
        ]
        return DetectionResult(
            comparisons=comparisons,
            metadata={"detector": self.name}
        )
```

### Creating a New Output Format

```python
from plagdet.plugins.base import OutputPlugin
from plagdet.core.models.detection import DetectionResult
from plagdet.core.registry import register_output

@register_output
class MyOutput(OutputPlugin):
    @property
    def name(self) -> str:
        return "my_output"

    def write(self, result: DetectionResult, output_path: str, config) -> None:
        # Your output logic here
        pass
```

## Available Detectors

### JPlag (Default)
- **Status**: ✅ Included
- **Installation**: Java + `jplag.jar` in working directory
- **Privacy**: Fully local
- **Best For**: Token-based analysis, widely trusted results

```yaml
detector:
  name: jplag
  config:
    language: python3
    token_length: 10
```

### MOSS (Stanford)
- **Status**: ⚙️ Requires setup
- **Installation**: `pip install mosspy` + [MOSS User ID registration](mailto:moss@moss.stanford.edu)
- **Privacy**: ⚠️ Sends code to external server
- **Best For**: Industry standard, widely accepted results

```yaml
detector:
  name: moss
  config:
    userid: YOUR_MOSS_ID
    language: python
    extensions: ["py"]
```

**To get MOSS ID**: Email `moss@moss.stanford.edu` with body:
```
registeruser
mail your.email@university.edu
```

### Dolos (Modern, Recommended)
- **Status**: ⚙️ Requires Node.js
- **Installation**: `npm install -g @dodona/dolos` + `pip install pandas`
- **Privacy**: ✅ Fully local
- **Best For**: Modern UI, CSV export, education-focused

```yaml
detector:
  name: dolos
  config:
    language: python
    min_similarity: 0.7
```

### CopyDetect
- **Status**: ✅ Python-native
- **Installation**: `pip install copydetect`
- **Privacy**: ✅ Fully local
- **Best For**: Python integration, HTML reports

```yaml
detector:
  name: copydetect
  config:
    extensions: ["py"]
    display_threshold: 0.33
```

### SIM (Lightweight)
- **Status**: ⚙️ Requires compilation
- **Installation**: Download from [dickgrune.com](http://dickgrune.com/Programs/similarity_tester/)
- **Privacy**: ✅ Fully local
- **Best For**: Fast, simple similarity checks

```yaml
detector:
  name: sim
  config:
    language: c
    threshold: 50
```

## Detector Comparison

| Detector | Local/Remote | Setup | Output | Algorithm |
|----------|--------------|-------|--------|-----------|
| **JPlag** | Local | Java + JAR | HTML/JSON | Token-based (Excellent) |
| **MOSS** | Remote | Email registration | HTML | Winnowing (Excellent) |
| **Dolos** | Local | npm install | Web/CSV | Tree-sitter (Very Good) |
| **CopyDetect** | Local | pip install | HTML | Token-based (Good) |
| **SIM** | Local | Compilation | Text | Simple matching (Basic) |

## Requirements

### Core Requirements
- Python >= 3.9
- `click`, `pyyaml`, `unidecode`

### Detector-Specific Requirements
- **JPlag**: Java + `jplag.jar`
- **MOSS**: `mosspy` package + MOSS user ID
- **Dolos**: Node.js + `@dodona/dolos` + `pandas`
- **CopyDetect**: `copydetect` package
- **SIM**: SIM executable (compile from source)

## License

MIT

## Author

Batuhan Edgüer
