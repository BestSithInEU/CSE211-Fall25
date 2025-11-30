#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  if (k >= this->size()) {
    throw std::out_of_range("Index out of range");
  }

  // Create a copy to traverse without modifying original
  StackQuestions<T> copy = *this;

  // Pop k elements to reach the kth element
  for (size_t i = 0; i < k; i++) {
    copy.pop();
  }

  return copy.top();
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  StackQuestions<T> tempStack;

  // Insertion sort using temp stack
  while (!this->isEmpty()) {
    T current = this->top();
    this->pop();

    // Move elements greater than current back to original stack
    while (!tempStack.isEmpty() && tempStack.top() > current) {
      this->push(tempStack.top());
      tempStack.pop();
    }

    tempStack.push(current);
  }

  // Transfer back: tempStack has largest on top, so result has smallest on top
  while (!tempStack.isEmpty()) {
    this->push(tempStack.top());
    tempStack.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
