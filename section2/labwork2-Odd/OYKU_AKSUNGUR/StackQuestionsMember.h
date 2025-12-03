#ifndef STACK_QUESTIONS_MEMBER_H
#define STACK_QUESTIONS_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T> class Stack; // Forward declaration

// Extend Stack with additional member functions
template <typename T> class StackQuestions : public Stack<T> {
public:
  using Stack<T>::Stack; // Inherit constructors

  /**
   * @brief Check if the stack is palindromic (reads same top-to-bottom as
   * bottom-to-top)
   * @return true if palindrome, false otherwise
   *
   * Time: O(n), Space: O(n)
   * Approach: Convert to vector and compare both ends
   */
  bool isPalindrome() const;

  /**
   * @brief Remove all duplicate elements, keeping only first occurrence
   *
   * Time: O(n²) worst case, Space: O(n)
   * Approach: Use temporary stack and track seen elements
   */
  void removeDuplicates();
};

// Include template implementation
#include "StackQuestionsMember.tpp"

#endif // STACK_QUESTIONS_MEMBER_H
