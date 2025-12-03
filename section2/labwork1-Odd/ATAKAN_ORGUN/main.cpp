// src/main.cpp
#include <iostream>
#include <string>

#include "../include/Color.h"
#include "../include/LinkedList.h"
#include "../include/LinkedListQuestions.h"

void printSectionHeader(const std::string &title) {
  std::cout
      << "\n"
      << Color::BOLD << Color::CYAN
      << "╔══════════════════════════════════════════════════════════════╗\n"
      << "║  " << title;
  // Padding to match 64 char total width: 1 (║) + 2 (spaces) + title + padding
  // + 1 (║) = 64
  for (size_t i = title.length(); i < 60; i++)
    std::cout << " ";
  std::cout
      << "║\n"
      << "╚══════════════════════════════════════════════════════════════╝"
      << Color::RESET << std::endl;
}

void printQuestionHeader(int num, const std::string &title) {
  std::cout << "\n"
            << Color::HEADER << "Q" << num << ": " << title << Color::RESET
            << std::endl;
}

void demonstrateQ1() {
  printQuestionHeader(1, "Check if List is Sorted");
  LinkedList<int> list1a;
  list1a.push_back(1);
  list1a.push_back(3);
  list1a.push_back(5);
  list1a.push_back(1);
  std::cout << "List A: ";
  list1a.print();
  std::cout << (isSorted(list1a) ? Color::SUCCESS : Color::ERROR)
            << "Is sorted: " << (isSorted(list1a) ? "Yes" : "No")
            << Color::RESET << std::endl;

  LinkedList<int> list1b;
  list1b.push_back(5);
  list1b.push_back(2);
  list1b.push_back(8);
  std::cout << "List B: ";
  list1b.print();
  std::cout << (isSorted(list1b) ? Color::SUCCESS : Color::ERROR)
            << "Is sorted: " << (isSorted(list1b) ? "Yes" : "No")
            << Color::RESET << std::endl;
}

void demonstrateQ2() {
  printQuestionHeader(2, "Split List into Two Halves");
  LinkedList<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);
  list2.push_back(4);
  list2.push_back(5);
  std::cout << "Original: ";
  list2.print();
  LinkedList<int> secondHalf = splitInHalf(list2);
  std::cout << "First half: ";
  list2.print();
  std::cout << "Second half: ";
  secondHalf.print();
}

void demonstrateQ3() {
  printQuestionHeader(3, "Find Nth Node from End");
  LinkedList<int> list3;
  list3.push_back(10);
  list3.push_back(20);
  list3.push_back(30);
  list3.push_back(40);
  list3.push_back(50);
  std::cout << "List: ";
  list3.print();
  int nthFromEnd;
  if (findNthFromEnd(list3, 2, nthFromEnd)) {
    std::cout << Color::SUCCESS << "2nd from end: " << nthFromEnd
              << Color::RESET << std::endl;
  }
}

void demonstrateQ4() {
  printQuestionHeader(4, "Partition List Around a Value");
  LinkedList<int> list4;
  list4.push_back(7);
  list4.push_back(2);
  list4.push_back(8);
  list4.push_back(3);
  list4.push_back(1);
  list4.push_back(6);
  std::cout << "Before: ";
  list4.print();
  partitionAroundValue(list4, 5);
  std::cout << "After partitioning around 5: ";
  list4.print();
  std::cout << Color::INFO << "(All values < 5 come before values >= 5)"
            << Color::RESET << std::endl;
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main(int argc, char *argv[]) {
  std::cout
      << Color::BOLD << Color::CYAN
      << "\n╔══════════════════════════════════════════════════════════════╗\n"
      << "║  LinkedList - 4 Coding Questions Demonstration                 ║\n"
      << "╚══════════════════════════════════════════════════════════════╝"
      << Color::RESET << std::endl;

  // If no arguments provided, run all questions
  if (argc == 1) {
    demonstrateQ1();
    demonstrateQ2();
    demonstrateQ3();
    demonstrateQ4();

    std::cout << "\n"
              << Color::SUCCESS << Color::BOLD
              << "✓ All 4 questions demonstrated successfully!" << Color::RESET
              << "\n"
              << std::endl;
  }
  // If argument provided, run specific question
  else if (argc == 2) {
    std::string arg = argv[1];
    int questionNum = -1;

    // Try to parse the question number
    try {
      questionNum = std::stoi(arg);
    } catch (...) {
      std::cerr << Color::ERROR << "Error: Invalid question number '" << arg
                << "'" << Color::RESET << std::endl;
      std::cerr << Color::INFO << "Usage: " << argv[0] << " [1|2|3|4]"
                << Color::RESET << std::endl;
      return 1;
    }

    // Run the specified question
    switch (questionNum) {
    case 1:
      demonstrateQ1();
      std::cout << "\n"
                << Color::SUCCESS << Color::BOLD << "✓ Question 1 completed!"
                << Color::RESET << "\n"
                << std::endl;
      break;
    case 2:
      demonstrateQ2();
      std::cout << "\n"
                << Color::SUCCESS << Color::BOLD << "✓ Question 2 completed!"
                << Color::RESET << "\n"
                << std::endl;
      break;
    case 3:
      demonstrateQ3();
      std::cout << "\n"
                << Color::SUCCESS << Color::BOLD << "✓ Question 3 completed!"
                << Color::RESET << "\n"
                << std::endl;
      break;
    case 4:
      demonstrateQ4();
      std::cout << "\n"
                << Color::SUCCESS << Color::BOLD << "✓ Question 4 completed!"
                << Color::RESET << "\n"
                << std::endl;
      break;
    default:
      std::cerr << Color::ERROR << "Error: Question " << questionNum
                << " does not exist" << Color::RESET << std::endl;
      std::cerr << Color::INFO << "Available questions: 1, 2, 3, 4"
                << Color::RESET << std::endl;
      return 1;
    }
  } else {
    std::cerr << Color::ERROR << "Error: Too many arguments" << Color::RESET
              << std::endl;
    std::cerr << Color::INFO << "Usage: " << argv[0] << " [1|2|3|4]"
              << Color::RESET << std::endl;
    return 1;
  }

  return 0;
}
