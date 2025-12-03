#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  Stack<T> tempStack = *this;
  std::vector<T> elements;

  for (; !tempStack.isEmpty(); tempStack.pop()) {
    elements.push_back(tempStack.top());
  }

  if (elements.empty()) {
    return true;
  }

  for (size_t left = 0, right = elements.size() - 1; left < right; left++, right--) {
    if (elements[left] != elements[right]) {
      return false;
    }
  }

  return true;
}



// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
  Stack<T> reversedStack = *this;
  this->clear();

  Stack<T> tempStack;
  std::set<T> seenElements;

  for (; !reversedStack.isEmpty(); reversedStack.pop()) {
    if (seenElements.insert(reversedStack.top()).second) {
      tempStack.push(reversedStack.top());
    }
  }

  for (; !tempStack.isEmpty(); tempStack.pop()) {
    this->push(tempStack.top());
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP