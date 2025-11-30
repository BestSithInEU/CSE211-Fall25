#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
T StackQuestions<T>::getKthFromTop(size_t k) const {
  if (k >= stack.size())
    throw std::out_of_range("k is out of range");

  std::stack<T> temp;
  // Pop k items into temp
  for (size_t i = 0; i < k; i++) {
    temp.push(stack.top());
    stack.pop();
  }

  // Now the kth element is on top
  T result = stack.top();

  // Restore original stack
  while (!temp.empty()) {
    stack.push(temp.top());
    temp.pop();
  }

  return result;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
void StackQuestions<T>::sortStack() {
  std::stack<T> temp;

  while (!stack.empty()) {
    T cur = stack.top();
    stack.pop();

    // Move larger elements back to main stack
    while (!temp.empty() && temp.top() > cur) {
      stack.push(temp.top());
      temp.pop();
    }

    temp.push(cur);
  }

  // Copy sorted values back to original stack
  while (!temp.empty()) {
    stack.push(temp.top());
    temp.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
