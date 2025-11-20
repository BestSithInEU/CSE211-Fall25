import csv
import json
import os
import shutil
import subprocess
import sys
import zipfile
from typing import Any, Dict, Optional, Set

import unidecode

# Color constants
COLOR_RED = "\033[91m"
COLOR_GREEN = "\033[92m"
COLOR_YELLOW = "\033[93m"
COLOR_RESET = "\033[0m"


def unzip_submissions(zip_file_path: str, output_dir: str) -> None:
    """
    Unzip student submission ZIP files into a labwork directory.

    Args:
        zip_file_path: Path to the ZIP file containing student submissions
        output_dir: Directory to extract submissions to
    """
    try:
        print(
            f"{COLOR_YELLOW}Unzipping submissions from {zip_file_path}...{COLOR_RESET}"
        )

        # Create output directory if it doesn't exist
        os.makedirs(output_dir, exist_ok=True)

        # Extract all files
        with zipfile.ZipFile(zip_file_path, "r") as zip_ref:
            zip_ref.extractall(output_dir)

        print(
            f"{COLOR_GREEN}Successfully extracted submissions to {output_dir}{COLOR_RESET}"
        )
    except Exception as e:
        print(f"{COLOR_RED}Failed to unzip submissions: {e}{COLOR_RESET}")


def run_jplag(
    zip_file_name: str,
    language: str,
    target_path: str,
    token_length: int,
    base_path: Optional[str] = None,
) -> None:
    """
    Run JPlag on the target directory with the specified parameters.

    Args:
        zip_file_name: Name of the zip file to be created
        language: Programming language of submissions
        target_path: Path to the directory containing submissions
        token_length: Minimum token length for matching
        base_path: Optional path to the base code directory
    """
    try:
        print(
            f"{COLOR_GREEN}Running JPlag for {zip_file_name} in language {language}...{COLOR_RESET}"
        )
        jplag_command = [
            "java",
            "-jar",
            "./jplag.jar",
            "-l",
            language,
            "-t",
            str(token_length),
            os.path.join(target_path),
        ]
        if base_path:
            jplag_command.extend(["-bc", os.path.join(target_path, base_path)])
            print(jplag_command)
            print(f"{COLOR_YELLOW}Using base path: {base_path}{COLOR_RESET}")
        subprocess.run(jplag_command, check=True, stdout=subprocess.DEVNULL)
        print(f"{COLOR_GREEN}JPlag run completed.{COLOR_RESET}")
    except subprocess.CalledProcessError as e:
        print(f"{COLOR_RED}Error running JPlag: {e}{COLOR_RESET}")


def unzip_file(zip_file_name: str, target_path: str) -> Optional[str]:
    """
    Unzip the JPlag results file.

    Args:
        zip_file_name: Name of the zip file to unzip
        target_path: Path to extract the files to

    Returns:
        Path to the extracted results directory or None if failed
    """
    try:
        print(
            f"{COLOR_YELLOW}Unzipping {zip_file_name} to {target_path}...{COLOR_RESET}"
        )
        results_directory = os.path.join(target_path, "results")
        os.makedirs(results_directory, exist_ok=True)
        with zipfile.ZipFile(zip_file_name, "r") as zip_ref:
            zip_ref.extractall(results_directory)
        print(f"{COLOR_GREEN}Unzipping completed.{COLOR_RESET}")
        return results_directory
    except Exception as e:
        print(f"{COLOR_RED}Failed to unzip file: {e}{COLOR_RESET}")
        return None


def move_file(file_name: str, target_path: str) -> None:
    """
    Move a file to the target directory.

    Args:
        file_name: Name of the file to move
        target_path: Destination directory
    """
    try:
        print(f"{COLOR_YELLOW}Moving {file_name} to {target_path}...{COLOR_RESET}")
        target_directory = os.path.join(target_path)
        os.makedirs(target_directory, exist_ok=True)
        target_file_path = os.path.join(target_directory, os.path.basename(file_name))
        if os.path.exists(target_file_path):
            os.remove(target_file_path)
        shutil.move(file_name, target_directory)
        print(f"{COLOR_GREEN}File move completed.{COLOR_RESET}")
    except Exception as e:
        print(f"{COLOR_RED}Failed to move file: {e}{COLOR_RESET}")


def load_json_data(results_directory: str) -> Optional[Dict[str, Any]]:
    """
    Load the JPlag results data from the overview.json file.

    Args:
        results_directory: Path to the directory containing the results

    Returns:
        Parsed JSON data or None if failed
    """
    try:
        print(
            f"{COLOR_YELLOW}Loading JSON data from {results_directory}...{COLOR_RESET}"
        )
        with open(
            os.path.join(results_directory, "overview.json"), "r", encoding="utf-8"
        ) as file:
            data = json.load(file)
        print(f"{COLOR_GREEN}JSON data loaded.{COLOR_RESET}")
        return data
    except Exception as e:
        print(f"{COLOR_RED}Failed to load JSON data: {e}{COLOR_RESET}")
        return None


def write_to_csv(
    data: Dict[str, Any], metric_key: str, min_score: float, target_path: str
) -> Set[str]:
    """
    Write plagiarism results to a CSV file.

    Args:
        data: JPlag results data
        metric_key: Similarity metric to use (AVG or MAX)
        min_score: Minimum similarity threshold
        target_path: Path to write the CSV file to

    Returns:
        Set of unique student names involved in plagiarism
    """
    try:
        output_filename = os.path.basename(target_path) + ".csv"
        output_filename = os.path.join(target_path, output_filename)
        unique_names = set()
        print(
            f"{COLOR_YELLOW}Writing results to CSV at {output_filename}...{COLOR_RESET}"
        )
        with open(output_filename, "w", newline="", encoding="utf-8") as csvfile:
            csvwriter = csv.writer(csvfile)
            csvwriter.writerow(["First Submission", "Second Submission", "Similarity"])
            for metric in data["metrics"]:
                if metric["name"].upper() == metric_key:
                    for comparison in metric["topComparisons"]:
                        if comparison["similarity"] * 100 >= min_score:
                            first_name = normalize_name(comparison["first_submission"])
                            second_name = normalize_name(
                                comparison["second_submission"]
                            )
                            csvwriter.writerow(
                                [first_name, second_name, comparison["similarity"]]
                            )
                            unique_names.update([first_name, second_name])
        print(f"{COLOR_GREEN}CSV writing completed.{COLOR_RESET}")
        return unique_names
    except Exception as e:
        print(f"{COLOR_RED}Failed to write CSV: {e}{COLOR_RESET}")
        return set()


def normalize_name(name: str) -> str:
    """
    Normalize Turkish characters in student names.

    Args:
        name: Student name to normalize

    Returns:
        Normalized name
    """
    replacements = {
        "Ç": "C",
        "ç": "c",
        "Ğ": "G",
        "ğ": "g",
        "İ": "I",
        "ı": "i",
        "Ö": "O",
        "ö": "o",
        "Ş": "S",
        "ş": "s",
    }
    for original, correct in replacements.items():
        name = name.replace(original, correct)

    return unidecode.unidecode(name.split("_")[0])


def write_unique_names(unique_names: Set[str], target_path: str) -> None:
    """
    Write the list of unique student names to a CSV file.

    Args:
        unique_names: Set of unique student names
        target_path: Path to write the CSV file to
    """
    unique_filename = os.path.join(target_path, "unique_names.csv")
    print(f"{COLOR_YELLOW}Writing unique names to {unique_filename}...{COLOR_RESET}")
    with open(unique_filename, "w", newline="", encoding="utf-8") as file:
        writer = csv.writer(file, delimiter=",")
        writer.writerow(["Name"])
        for name in sorted(unique_names):
            writer.writerow([name])
    print(f"{COLOR_GREEN}Unique names writing completed.{COLOR_RESET}")


def delete_directory(directory_path: str) -> None:
    """
    Delete a directory and all its contents.

    Args:
        directory_path: Path to the directory to delete
    """
    try:
        print(f"{COLOR_YELLOW}Deleting directory {directory_path}...{COLOR_RESET}")
        shutil.rmtree(directory_path)
        print(f"{COLOR_GREEN}Directory deleted.{COLOR_RESET}")
    except Exception as e:
        print(f"{COLOR_RED}Failed to delete directory: {e}{COLOR_RESET}")


def extract_and_process(
    zip_file_name: str,
    metric_key: str,
    min_score: float,
    language: str,
    token_length: int,
    target_path: str,
    base_path: Optional[str] = None,
) -> None:
    """
    Main processing function that runs JPlag and processes the results.

    Args:
        zip_file_name: Name of the zip file to be created
        metric_key: Similarity metric to use (AVG or MAX)
        min_score: Minimum similarity threshold
        language: Programming language of submissions
        token_length: Minimum token length for matching
        target_path: Path to the directory containing submissions
        base_path: Optional path to the base code directory
    """
    try:
        print(f"{COLOR_YELLOW}Starting extraction and processing...{COLOR_RESET}")
        run_jplag(zip_file_name, language, target_path, token_length, base_path)
        results_directory = unzip_file(zip_file_name, target_path)
        move_file(zip_file_name, target_path)
        data = load_json_data(results_directory)
        unique_names = write_to_csv(data, metric_key, min_score, target_path)
        write_unique_names(unique_names, target_path)
        delete_directory(results_directory)
        print(f"{COLOR_GREEN}Extraction and processing completed.{COLOR_RESET}")
    except Exception as e:
        print(f"{COLOR_RED}Failed to process: {e}{COLOR_RESET}")


def main() -> None:
    """
    Main entry point for the script when run as a module.
    """
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)

    command = sys.argv[1].lower()

    if command == "unzip":
        if len(sys.argv) != 4:
            print("Usage: poetry run jplag unzip <zip_file_path> <output_directory>")
            sys.exit(1)

        zip_file_path = sys.argv[2]
        output_dir = sys.argv[3]
        unzip_submissions(zip_file_path, output_dir)

    elif command in ["avg", "max"]:
        # For AVG/MAX commands, we need at least 6 arguments total (command + 5 parameters)
        # and at most 7 arguments total (command + 5 parameters + optional base_path)
        if len(sys.argv) < 6 or len(sys.argv) > 7:
            print_usage()
            sys.exit(1)

        metric_key = command.upper()
        min_score = float(sys.argv[2])
        language = sys.argv[3]
        token_length = int(sys.argv[4])
        target_path = sys.argv[5]
        base_path = sys.argv[6] if len(sys.argv) == 7 else None

        extract_and_process(
            "result.zip",
            metric_key,
            min_score,
            language,
            token_length,
            target_path,
            base_path,
        )
    else:
        print_usage()
        sys.exit(1)


def print_usage() -> None:
    """
    Print usage information for the script.
    """
    print(
        "Usage:\n"
        "  1. Run JPlag:\n"
        "     poetry run jplag <metric_key> <min_score> <language> <token_length> <target_path> [base_path]\n"
        "     <metric_key>: AVG, MAX\n"
        "     <min_score>: 0.0 - 100.0\n"
        "     <language>: cpp (C/C++ Scanner), cpp2 (C/C++ Parser), csharp, emf, go, java, kotlin, python3, rlang, rust, scala, scheme, swift, text\n"
        "     <token_length>: Minimum token length for matching (higher values focus on larger matching sections)\n"
        "     <target_path>: path to the folder containing the submissions\n"
        "     [base_path]: optional path to the folder containing the base submission (relative to target_path)\n\n"
        "  2. Unzip submissions:\n"
        "     poetry run jplag unzip <zip_file_path> <output_directory>\n"
        "     <zip_file_path>: path to the ZIP file containing student submissions\n"
        "     <output_directory>: directory to extract submissions to\n"
    )


if __name__ == "__main__":
    main()
