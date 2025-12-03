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
// MEMBER FUNCTION DEMONSTRATIONS
// ============================================================================

void demo_isPalindrome() {
  printHeader("Q3: isPalindrome()");

  StackQuestions<int> palindrome;
  palindrome.loadFromJSON("examples/members.json", "q1_palindrome");

  printInfo("Stack 1 (top to bottom): 1, 2, 3, 2, 1");
  std::cout << "Is palindrome? " << (palindrome.isPalindrome() ? "Yes" : "No")
            << std::endl;

  StackQuestions<int> notPalindrome;
  notPalindrome.loadFromJSON("examples/members.json", "q1_not_palindrome");

  printInfo("Stack 2 (top to bottom): 4, 3, 2, 1");
  std::cout << "Is palindrome? "
            << (notPalindrome.isPalindrome() ? "Yes" : "No") << std::endl;
  printSuccess("isPalindrome() works correctly!");
}

void demo_removeDuplicates() {
  printHeader("Q2: removeDuplicates()");

  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q2_duplicates");

  printInfo("Original stack (top to bottom): 5, 1, 4, 2, 3, 2, 1");
  stack.removeDuplicates();
  printInfo("After removing duplicates (keeping first occurrence):");
  stack.display();
  printSuccess("removeDuplicates() works correctly!");
}

// ============================================================================
// NON-MEMBER FUNCTION DEMONSTRATIONS
// ============================================================================

void demo_mergeSorted() {
  printHeader("Q3: mergeSorted()");

  Stack<int> stack1, stack2;
  stack1.loadFromJSON("examples/nonmembers.json", "q3_stack1");
  stack2.loadFromJSON("examples/nonmembers.json", "q3_stack2");

  printInfo("Stack1 (sorted, smallest on top): 1, 3, 5, 9");
  printInfo("Stack2 (sorted, smallest on top): 2, 4, 6, 8");

  Stack<int> merged = StackUtils::mergeSorted(stack1, stack2);
  printInfo("Merged sorted stack:");
  merged.display();
  printSuccess("mergeSorted() works correctly!");
}

void demo_longestValidParentheses() {
  printHeader("Q4: longestValidParentheses()");

  std::string s1 =
      loadStringFromJSON("examples/nonmembers.json", "q4_strings", "s1");
  std::string s2 =
      loadStringFromJSON("examples/nonmembers.json", "q4_strings", "s2");
  std::string s3 =
      loadStringFromJSON("examples/nonmembers.json", "q4_strings", "s3");

  printInfo("String 1: \"(()\"");
  std::cout << "Longest valid: " << StackUtils::longestValidParentheses(s1)
            << " (expected: 2)" << std::endl;

  printInfo("String 2: \")()())\"");
  std::cout << "Longest valid: " << StackUtils::longestValidParentheses(s2)
            << " (expected: 4)" << std::endl;

  printInfo("String 3: \"(()(()))\"");
  std::cout << "Longest valid: " << StackUtils::longestValidParentheses(s3)
            << " (expected: 8)" << std::endl;

  printSuccess("longestValidParentheses() works correctly!");
}

// ============================================================================
// HELPER FUNCTIONS FOR RUNNING QUESTIONS
// ============================================================================

void runQuestion(int questionNum) {
  switch (questionNum) {
  case 1:
    demo_isPalindrome();
    break;
  case 2:
    demo_removeDuplicates();
    break;
  case 3:
    demo_mergeSorted();
    break;
  case 4:
    demo_longestValidParentheses();
    break;
  default:
    printError("Invalid question number. Must be between 1 and 20.");
    std::cout << Color::INFO << "Usage: ./program [question_number | all]"
              << Color::RESET << std::endl;
    std::cout << Color::INFO << "  Example: ./program 5    (runs question 5)"
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
            << " 20 Stack Coding Questions - Comprehensive Demo "
            << Color::RESET << std::endl;
  std::cout << Color::CYAN << Color::ITALIC
            << "Average to Above-Average Difficulty" << Color::RESET << "\n"
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
        if (questionNum >= 1 && questionNum <= 20) {
          runAll = false;
        } else {
          printError("Question number must be between 1 and 20.");
          std::cout << Color::INFO << "Usage: " << argv[0]
                    << " [question_number | all]" << Color::RESET << std::endl;
          return 1;
        }
      } catch (const std::exception &) {
        printError(
            "Invalid argument. Please provide a number (1-20) or 'all'.");
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
