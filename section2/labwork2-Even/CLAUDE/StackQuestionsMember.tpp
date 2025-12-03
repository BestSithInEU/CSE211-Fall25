#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  if (this->isEmpty()) {
    return 0;
  }

  Stack<T> temp;
  size_t maxLen = 1;
  size_t currentLen = 1;

  // Copy stack to temp (reversed)
  Stack<T> copy = *this;
  while (!copy.isEmpty()) {
    temp.push(copy.top());
    copy.pop();
  }

  // Now temp has elements in original order (bottom to top)
  T prev = temp.top();
  temp.pop();

  while (!temp.isEmpty()) {
    T curr = temp.top();
    temp.pop();

    if (curr == prev + 1) {
      currentLen++;
      maxLen = std::max(maxLen, currentLen);
    } else {
      currentLen = 1;
    }
    prev = curr;
  }

  return maxLen;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  if (this->isEmpty() || k <= 0) {
    return;
  }

  size_t n = this->size();
  k = k % n;
  if (k == 0) {
    return;
  }

  // Move all elements to auxiliary stack (reversing order)
  Stack<T> aux;
  while (!this->isEmpty()) {
    aux.push(this->top());
    this->pop();
  }

  // aux now has elements in reversed order
  // We need to rotate: move bottom k elements to top
  // First, move (n - k) elements back to original stack
  Stack<T> temp;
  for (size_t i = 0; i < n - k; i++) {
    temp.push(aux.top());
    aux.pop();
  }

  // Move remaining k elements (these go to bottom)
  while (!aux.isEmpty()) {
    this->push(aux.top());
    aux.pop();
  }

  // Move the (n - k) elements back on top
  while (!temp.isEmpty()) {
    this->push(temp.top());
    temp.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
