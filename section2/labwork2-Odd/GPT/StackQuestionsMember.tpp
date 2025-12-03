#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  if (stack_.empty())
    return true;

  Stack<T> temp = stack_;
  std::vector<T> arr;

  while (!temp.empty()) {
    arr.push_back(temp.top());
    temp.pop();
  }

  int l = 0, r = arr.size() - 1;
  while (l < r) {
    if (arr[l] != arr[r])
      return false;
    l++, r--;
  }
  return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
  Stack<T> temp;
  std::unordered_set<T> seen;

  while (!stack_.empty()) {
    T v = stack_.top();
    stack_.pop();
    if (!seen.count(v)) {
      seen.insert(v);
      temp.push(v);
    }
  }

  // Reverse to restore order
  Stack<T> finalStack;
  while (!temp.empty()) {
    finalStack.push(temp.top());
    temp.pop();
  }
  stack_ = finalStack;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
