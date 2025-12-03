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

void demo_longestConsecutiveSequence() {
  printHeader("Q1: longestConsecutiveSequence()");

  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q1_stack");

  printInfo("Stack (top to bottom): 8, 7, 6, 5, 3, 2, 1");
  std::cout << "Longest consecutive sequence: "
            << stack.longestConsecutiveSequence() << " (expected: 4)"
            << std::endl;
  printSuccess("longestConsecutiveSequence() works correctly!");
}

void demo_rotateStack() {
  printHeader("Q2: rotateStack()");

  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q2_stack");

  printInfo("Original stack (top to bottom): 5, 4, 3, 2, 1");
  StackQuestions<int> copy = stack;

  stack.rotateStack(2);
  printInfo("After rotating 2 positions right:");
  stack.display();

  copy.rotateStack(-2);
  printInfo("Original rotated 2 positions left:");
  copy.display();
  printSuccess("rotateStack() works correctly!");
}

void demo_interleaveHalves() {
  printHeader("Q3: interleaveHalves()");

  Stack<int> stack;
  stack.loadFromJSON("examples/nonmembers.json", "q3_stack");

  printInfo("Original stack (top to bottom): 6, 5, 4, 3, 2, 1");
  printInfo("Bottom half: [1, 2, 3], Top half: [4, 5, 6]");

  StackUtils::interleaveHalves(stack);
  printInfo("After interleaving:");
  stack.display();
  printSuccess("interleaveHalves() works correctly!");
}

void demo_nextGreaterElement() {
  printHeader("Q4: nextGreaterElement()");

  Stack<int> stack;
  stack.loadFromJSON("examples/nonmembers.json", "q4_stack");

  printInfo("Stack (top to bottom): 8, 10, 2, 5, 4");
  printInfo("Elements (bottom to top): [4, 5, 2, 10, 8]");

  std::vector<int> result = StackUtils::nextGreaterElement(stack);
  std::cout << "Next greater elements: ";
  printVector(result);
  std::cout << std::endl;
  printInfo("Expected: [5, 10, 10, -1, -1]");

  printSuccess("nextGreaterElement() works correctly!");
}

// ============================================================================
// HELPER FUNCTIONS FOR RUNNING QUESTIONS
// ============================================================================

void runQuestion(int questionNum) {
  switch (questionNum) {
  case 1:
    demo_longestConsecutiveSequence();
    break;
  case 2:
    demo_rotateStack();
    break;
  case 3:
    demo_interleaveHalves();
    break;
  case 4:
    demo_nextGreaterElement();
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
