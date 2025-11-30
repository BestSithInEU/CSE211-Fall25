"""
Service for safe file system access
"""

import os
from pathlib import Path
from typing import Tuple, Optional


class FileService:
    """Service for safe file access with path traversal protection"""

    def __init__(self, base_dir: str = "."):
        # If relative path, resolve relative to project root (parent of backend/)
        if base_dir == ".":
            # Backend runs from backend/ directory, so go up one level to project root
            self.base_dir = Path(__file__).parent.parent.parent.resolve()
        else:
            self.base_dir = Path(base_dir).resolve()

    def _validate_path(self, path: str) -> Path:
        """
        Validate that path is within base_dir (prevents path traversal)
        Raises ValueError if path is outside base_dir
        """
        requested_path = (self.base_dir / path).resolve()

        if not str(requested_path).startswith(str(self.base_dir)):
            raise ValueError(f"Access denied: Path traversal detected")

        return requested_path

    def read_file(self, relative_path: str) -> str:
        """
        Read file content safely
        Raises: ValueError for invalid paths, FileNotFoundError if not exists
        """
        file_path = self._validate_path(relative_path)

        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {relative_path}")

        if not file_path.is_file():
            raise ValueError(f"Not a file: {relative_path}")

        # Limit file size to 1MB for safety
        if file_path.stat().st_size > 1024 * 1024:
            raise ValueError(f"File too large (max 1MB): {relative_path}")

        return file_path.read_text(encoding='utf-8', errors='replace')

    def read_comparison_files(
        self,
        project_path: str,
        file1: str,
        file2: str
    ) -> Tuple[str, str]:
        """
        Read two files for comparison
        Returns: (content1, content2)
        """
        content1 = self.read_file(f"{project_path}/{file1}")
        content2 = self.read_file(f"{project_path}/{file2}")
        return content1, content2

    def detect_language(self, filename: str) -> str:
        """Detect programming language from file extension"""
        ext = Path(filename).suffix.lower()
        language_map = {
            '.py': 'python',
            '.cpp': 'cpp',
            '.cc': 'cpp',
            '.cxx': 'cpp',
            '.c': 'c',
            '.h': 'c',
            '.hpp': 'cpp',
            '.java': 'java',
            '.js': 'javascript',
            '.ts': 'typescript',
            '.jsx': 'jsx',
            '.tsx': 'tsx',
            '.go': 'go',
            '.rs': 'rust',
            '.rb': 'ruby',
            '.php': 'php',
            '.cs': 'csharp',
            '.swift': 'swift',
            '.kt': 'kotlin',
        }
        return language_map.get(ext, 'text')

    def list_directory(self, relative_path: str = ".") -> list[str]:
        """List files in directory (safe)"""
        dir_path = self._validate_path(relative_path)

        if not dir_path.exists():
            raise FileNotFoundError(f"Directory not found: {relative_path}")

        if not dir_path.is_dir():
            raise ValueError(f"Not a directory: {relative_path}")

        return [str(p.relative_to(self.base_dir)) for p in dir_path.iterdir()]

    def exists(self, relative_path: str) -> bool:
        """Check if file/directory exists (safe)"""
        try:
            path = self._validate_path(relative_path)
            return path.exists()
        except ValueError:
            return False
