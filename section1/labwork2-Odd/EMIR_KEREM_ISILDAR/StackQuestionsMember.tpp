#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  if (k >= this->size()) {
    throw std::out_of_range("k is out of range");
  }

  Stack<T> tempStack(*this);
  while (k-- > 0) {
    tempStack.pop();
  }
  return tempStack.top();
}

// ============================================================================
// Question 2: sortStack  bubblesort**
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  if (this->size() <= 1) {
    return;
  }

  Stack<T> tempStack;
  const size_t n = this->size();

  for (size_t pass = 0; pass < n; ++pass) {
    size_t comparisons = n - pass - 1;
    if (comparisons == 0) {
      break;
    }

    T first = this->top();
    this->pop();
    bool swapped = false;

    for (size_t i = 0; i < comparisons && !this->isEmpty(); ++i) {
      T second = this->top();
      this->pop();

      if (first < second) {
        tempStack.push(first);
        first = second;
        swapped = true;
      } else {
        tempStack.push(second);
      }
    }

    tempStack.push(first);

    while (!tempStack.isEmpty()) {
      this->push(tempStack.top());
      tempStack.pop();
    }

    if (!swapped) {
      break;
    }
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
