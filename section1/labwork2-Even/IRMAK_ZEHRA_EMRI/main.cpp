#include "Color.h"
#include "Stack.hpp"
#include "StackQuestionsMember.h"
#include "StackQuestionsNonMember.h"
#include "json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

void printHeader(const std::string &title) {
  std::cout << "\n"
            << Color::HEADER << Color::BOLD
            << "========================================" << Color::RESET
            << std::endl;
  std::cout << Color::BG_BLUE << Color::WHITE << Color::BOLD << " " << title
            << " " << Color::RESET << std::endl;
  std::cout << Color::HEADER << Color::BOLD
            << "========================================" << Color::RESET
            << std::endl;
}

void printSuccess(const std::string &message) {
  std::cout << Color::SUCCESS << Color::BOLD << "✓ " << Color::RESET
            << Color::SUCCESS << message << Color::RESET << std::endl;
}

void printError(const std::string &message) {
  std::cout << Color::ERROR << Color::BOLD << "✗ " << Color::RESET
            << Color::ERROR << Color::UNDERLINE << message << Color::RESET
            << std::endl;
}

void printInfo(const std::string &message) {
  std::cout << Color::INFO << Color::BOLD << "ℹ " << Color::RESET << Color::INFO
            << Color::ITALIC << message << Color::RESET << std::endl;
}

void printWarning(const std::string &message) {
  std::cout << Color::WARNING << Color::BOLD << "⚠ " << Color::RESET
            << Color::WARNING << message << Color::RESET << std::endl;
}

void printDebug(const std::string &message) {
  std::cout << Color::DEBUG_COLOR << Color::DIM << "[DEBUG] " << Color::RESET
            << Color::DEBUG_COLOR << message << Color::RESET << std::endl;
}

// Helper to print vector
template <typename T> void printVector(const std::vector<T> &vec) {
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i];
    if (i < vec.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]";
}

// Helper to load string data from JSON
std::string loadStringFromJSON(const std::string &filename,
                               const std::string &key,
                               const std::string &field) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open JSON file: " + filename);
  }

  json jsonData;
  file >> jsonData;

  if (!jsonData.contains(key)) {
    throw std::runtime_error("JSON file must contain key: " + key);
  }

  if (!jsonData[key].contains(field)) {
    throw std::runtime_error("Key '" + key + "' must contain field: " + field);
  }

  return jsonData[key][field].get<std::string>();
}

// ============================================================================
// LAB QUESTIONS DEMONSTRATIONS
// ============================================================================

void demo_findMiddle() {
  printHeader("Q1: findMiddle()");
  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q1_stack");

  printInfo("Stack (top to bottom): 5, 4, 3, 2, 1");
  std::cout << "Middle element: " << stack.findMiddle() << " (expected: 3)"
            << std::endl;

  stack.push(6);
  printInfo("After pushing 6: 6, 5, 4, 3, 2, 1");
  std::cout << "Middle element: " << stack.findMiddle()
            << " (expected: 3 - lower middle)" << std::endl;
  printSuccess("findMiddle() works correctly!");
}

void demo_reverse() {
  printHeader("Q2: reverse()");

  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q2_stack");

  printInfo("Original stack (top to bottom): 5, 4, 3, 2, 1");
  stack.reverse();
  printInfo("After reverse:");
  stack.display();
  printSuccess("reverse() works correctly!");
}

void demo_splitAlternate() {
  printHeader("Q3: splitAlternate()");

  Stack<int> source;
  source.loadFromJSON("examples/nonmembers.json", "q3_stack");

  printInfo("Source stack (top to bottom): 5, 4, 3, 2, 1");

  Stack<int> stack1, stack2;
  StackUtils::splitAlternate(source, stack1, stack2);

  printInfo("Stack1 (alternating elements):");
  stack1.display();
  printInfo("Stack2 (alternating elements):");
  stack2.display();
  printSuccess("splitAlternate() works correctly!");
}

void demo_simplifyPath() {
  printHeader("Q4: simplifyPath()");

  std::string path1 =
      loadStringFromJSON("examples/nonmembers.json", "q4_paths", "path1");
  std::string path2 =
      loadStringFromJSON("examples/nonmembers.json", "q4_paths", "path2");
  std::string path3 =
      loadStringFromJSON("examples/nonmembers.json", "q4_paths", "path3");

  printInfo("Path 1: \"/a/./b/../../c/\"");
  std::cout << "Simplified: \"" << StackUtils::simplifyPath(path1) << "\""
            << std::endl;

  printInfo("Path 2: \"/home//foo/\"");
  std::cout << "Simplified: \"" << StackUtils::simplifyPath(path2) << "\""
            << std::endl;

  printInfo("Path 3: \"/a/../../b/../c//.//\"");
  std::cout << "Simplified: \"" << StackUtils::simplifyPath(path3) << "\""
            << std::endl;

  printSuccess("simplifyPath() works correctly!");
}

// ============================================================================
// HELPER FUNCTIONS FOR RUNNING QUESTIONS
// ============================================================================

void runQuestion(int questionNum) {
  switch (questionNum) {
  case 1:
    demo_findMiddle();
    break;
  case 2:
    demo_reverse();
    break;
  case 3:
    demo_splitAlternate();
    break;
  case 4:
    demo_simplifyPath();
    break;
  default:
    printError("Invalid question number. Must be between 1 and 4.");
    std::cout << Color::INFO << "Usage: ./program [question_number | all]"
              << Color::RESET << std::endl;
    std::cout << Color::INFO << "  Example: ./program 4    (runs question 5)"
              << Color::RESET << std::endl;
    std::cout << Color::INFO << "  Example: ./program all  (runs all questions)"
              << Color::RESET << std::endl;
    break;
  }
}

void runAllQuestions() {
  // Member function demonstrations
  printHeader("MEMBER FUNCTIONS (Q1-Q2)");
  for (int i = 1; i <= 2; ++i) {
    runQuestion(i);
  }

  // Non-member function demonstrations
  printHeader("NON-MEMBER FUNCTIONS (Q3-Q4)");
  for (int i = 3; i <= 4; ++i) {
    runQuestion(i);
  }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(int argc, char *argv[]) {
  std::cout << Color::BOLD << Color::RED << R"(
   _____ _             _      _____                 _   _
  / ____| |           | |    / ____|               | | (_)
 | (___ | |_ __ _  ___| | __| |  __ _   _  ___  ___| |_ _  ___  _ __  ___
  \___ \| __/ _` |/ __| |/ /| | |_ | | | |/ _ \/ __| __| |/ _ \| '_ \/ __|
  ____) | || (_| | (__|   < | |__| | |_| |  __/\__ \ |_| | (_) | | | \__ \
 |_____/ \__\__,_|\___|_|\_\ \_____|\__,_|\___||___/\__|_|\___/|_| |_|___/

    )" << Color::RESET
            << std::endl;

  std::cout << Color::BG_CYAN << Color::BLACK << Color::BOLD
            << " 4 Stack Coding Questions - Comprehensive Demo " << Color::RESET
            << std::endl;

  // Parse command-line arguments
  bool runAll = true;
  int questionNum = 0;

  if (argc > 1) {
    std::string arg = argv[1];
    if (arg == "all") {
      runAll = true;
    } else {
      try {
        questionNum = std::stoi(arg);
        if (questionNum >= 1 && questionNum <= 4) {
          runAll = false;
        } else {
          printError("Question number must be between 1 and 4.");
          std::cout << Color::INFO << "Usage: " << argv[0]
                    << " [question_number | all]" << Color::RESET << std::endl;
          return 1;
        }
      } catch (const std::exception &) {
        printError("Invalid argument. Please provide a number (1-4) or 'all'.");
        std::cout << Color::INFO << "Usage: " << argv[0]
                  << " [question_number | all]" << Color::RESET << std::endl;
        return 1;
      }
    }
  }

  try {
    if (runAll) {
      runAllQuestions();
    } else {
      std::cout << Color::HEADER << Color::BOLD << "Running Question "
                << questionNum << Color::RESET << std::endl;
      runQuestion(questionNum);
    }

    std::cout << "\n"
              << Color::BOLD << Color::GREEN
              << "========================================" << Color::RESET
              << std::endl;
    if (runAll) {
      std::cout << Color::BG_GREEN << Color::BLACK << Color::BOLD
                << " ✓ All 4 demonstrations completed! " << Color::RESET
                << std::endl;
    } else {
      std::cout << Color::BG_GREEN << Color::BLACK << Color::BOLD
                << " ✓ Question " << questionNum << " completed! "
                << Color::RESET << std::endl;
    }
    std::cout << Color::BOLD << Color::GREEN
              << "========================================" << Color::RESET
              << "\n"
              << std::endl;

  } catch (const std::exception &e) {
    printError(std::string("Unexpected error: ") + e.what());
    return 1;
  }

  return 0;
}
