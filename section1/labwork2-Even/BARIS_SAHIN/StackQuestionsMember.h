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
   * @brief Find the middle element of the stack
   * @return The middle element (if odd size) or lower-middle (if even size)
   * @throws std::underflow_error if stack is empty
   *
   * Time: O(n), Space: O(n)
   * Approach: Calculate middle position using size, then traverse
   */
  T findMiddle() const;

  /**
   * @brief Reverse the stack using only stack operations (no extra containers)
   *
   * Time: O(nÂ²), Space: O(n) recursive stack
   * Approach: Recursion with insertAtBottom helper
   */
  void reverse();
};

// Include template implementation
#include "StackQuestionsMember.tpp"

#endif // STACK_QUESTIONS_MEMBER_H
