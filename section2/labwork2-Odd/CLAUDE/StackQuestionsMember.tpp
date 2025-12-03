#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  if (this->isEmpty()) {
    return true;
  }

  Stack<T> temp;
  Stack<T> copy;
  Stack<T> reversed;

  // Copy the original stack to temp (reversed order)
  Stack<T> original = *this;
  while (!original.isEmpty()) {
    T val = original.top();
    original.pop();
    temp.push(val);
  }

  // Copy temp to both copy and reversed (copy is now in original order)
  while (!temp.isEmpty()) {
    T val = temp.top();
    temp.pop();
    copy.push(val);
    reversed.push(val);
  }

  // Reverse 'reversed' to get reversed order
  while (!copy.isEmpty()) {
    T val = copy.top();
    copy.pop();
    temp.push(val);
  }

  // Now temp has original order, reversed has reversed order
  // Re-reverse to get proper comparison
  while (!reversed.isEmpty()) {
    T val = reversed.top();
    reversed.pop();
    copy.push(val);
  }

  // Compare temp (original order) with copy (reversed order)
  while (!temp.isEmpty()) {
    if (temp.top() != copy.top()) {
      return false;
    }
    temp.pop();
    copy.pop();
  }

  return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
  if (this->isEmpty()) {
    return;
  }

  Stack<T> temp;
  Stack<T> result;

  // Transfer all elements to temp (reversed)
  while (!this->isEmpty()) {
    T val = this->top();
    this->pop();
    temp.push(val);
  }

  // Process elements, keeping only first occurrence
  while (!temp.isEmpty()) {
    T val = temp.top();
    temp.pop();

    // Check if val exists in result
    Stack<T> check;
    bool found = false;

    while (!result.isEmpty()) {
      T curr = result.top();
      result.pop();
      check.push(curr);
      if (curr == val) {
        found = true;
      }
    }

    // Restore result
    while (!check.isEmpty()) {
      result.push(check.top());
      check.pop();
    }

    // Only add if not found
    if (!found) {
      result.push(val);
    }
  }

  // Transfer result back to this (need to reverse)
  while (!result.isEmpty()) {
    temp.push(result.top());
    result.pop();
  }

  while (!temp.isEmpty()) {
    this->push(temp.top());
    temp.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
