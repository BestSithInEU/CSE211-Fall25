// src/main.cpp
#include <iostream>
#include <string>
#include <vector>

#include "../include/Color.h"
#include "../include/LinkedList.h"
#include "../include/LinkedListQuestions.h"

void printSectionHeader(const std::string& title) {
  const size_t BOX_INNER_WIDTH = 62;
  size_t totalPadding = BOX_INNER_WIDTH - title.length();
  size_t leftPadding = totalPadding / 2;
  size_t rightPadding = totalPadding - leftPadding;

  std::cout
      << "\n"
      << Color::BOLD << Color::CYAN
      << "╔══════════════════════════════════════════════════════════════╗\n"
      << "║";
  for (size_t i = 0; i < leftPadding; i++) std::cout << " ";
  std::cout << title;
  for (size_t i = 0; i < rightPadding; i++) std::cout << " ";
  std::cout
      << "║\n"
      << "╚══════════════════════════════════════════════════════════════╝"
      << Color::RESET << std::endl;
}

void printQuestionHeader(int num, const std::string& title) {
  std::cout << "\n"
            << Color::HEADER << "Q" << num << ": " << title << Color::RESET
            << std::endl;
}

void printLevelHeader(const std::string& level) {
  std::cout << "\n"
            << Color::BOLD << Color::YELLOW << "═══════════════ " << level
            << " ═══════════════" << Color::RESET << std::endl;
}

// ============================================================================
// BASIC LEVEL (Q1-Q7)
// ============================================================================

void demonstrateQuestion1() {
  printQuestionHeader(6, "Display List in Reverse");
  LinkedList<int> list6;
  list6.push_back(1);
  list6.push_back(2);
  list6.push_back(3);
  list6.push_back(4);
  std::cout << "Original: ";
  list6.print();
  std::cout << Color::INFO << "Reversed: ";
  displayReverse(list6);
  std::cout << Color::RESET;
}

void demonstrateQuestion2() {
  printQuestionHeader(11, "Swap Adjacent Nodes Pairwise");
  LinkedList<int> list11;
  list11.push_back(1);
  list11.push_back(2);
  list11.push_back(3);
  list11.push_back(4);
  list11.push_back(5);
  std::cout << "Before: ";
  list11.print();
  swapAdjacent(list11);
  std::cout << "After swapping: ";
  list11.print();
}

void demonstrateQuestion3() {
  printQuestionHeader(16, "Rotate List by K Positions");
  LinkedList<int> list16;
  list16.push_back(1);
  list16.push_back(2);
  list16.push_back(3);
  list16.push_back(4);
  list16.push_back(5);
  std::cout << "Before: ";
  list16.print();
  rotateRight(list16, 2);
  std::cout << "After rotating right by 2: ";
  list16.print();
}

void demonstrateQuestion4() {
  // Q15: Merge Two Lists Alternately
  printQuestionHeader(15, "Merge Two Lists Alternately");
  LinkedList<int> list15a;
  list15a.push_back(1);
  list15a.push_back(3);
  list15a.push_back(5);
  LinkedList<int> list15b;
  list15b.push_back(2);
  list15b.push_back(4);
  list15b.push_back(6);
  std::cout << "List 1: ";
  list15a.print();
  std::cout << "List 2: ";
  list15b.print();
  LinkedList<int> merged = mergeAlternately(list15a, list15b);
  std::cout << "Merged: ";
  merged.print();
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main(int argc, char* argv[]) {
  printSectionHeader("LinkedList - Lab Exam");

  // If a question number is provided, run only that question
  if (argc > 1) {
    std::string arg = argv[1];

    // Check if "all" was specified
    if (arg == "all") {
      demonstrateQuestion1();
      demonstrateQuestion2();
      demonstrateQuestion3();
      demonstrateQuestion4();

      std::cout << "\n"
                << Color::SUCCESS << Color::BOLD
                << "✓ All 4 questions demonstrated successfully!"
                << Color::RESET << "\n"
                << std::endl;
    } else {
      // Try to parse as question number
      try {
        int question = std::stoi(arg);
        switch (question) {
          case 1:
            demonstrateQuestion1();
            break;
          case 2:
            demonstrateQuestion2();
            break;
          case 3:
            demonstrateQuestion3();
            break;
          case 4:
            demonstrateQuestion4();
            break;
          default:
            std::cerr << Color::ERROR << "Invalid question number: " << question
                      << Color::RESET << std::endl;
            std::cerr << "Please use 1, 2, 3, 4, or 'all'" << std::endl;
            return 1;
        }
        std::cout << "\n"
                  << Color::SUCCESS << Color::BOLD << "✓ Question " << question
                  << " demonstrated successfully!" << Color::RESET << "\n"
                  << std::endl;
      } catch (const std::invalid_argument&) {
        std::cerr << Color::ERROR << "Invalid argument: " << arg << Color::RESET
                  << std::endl;
        std::cerr << "Please use 1, 2, 3, 4, or 'all'" << std::endl;
        return 1;
      }
    }
  } else {
    // Run all questions
    demonstrateQuestion1();
    demonstrateQuestion2();
    demonstrateQuestion3();
    demonstrateQuestion4();

    std::cout << "\n"
              << Color::SUCCESS << Color::BOLD
              << "✓ All 4 questions demonstrated successfully!" << Color::RESET
              << "\n"
              << std::endl;
  }

  return 0;
}
