#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {

  // pushing to another stack reverses the order, so we can split in half and compare

  if (this->isEmpty()) {
    return true;
  }

  Stack<T> temp(*this);
  Stack<T> firstHalf;
  
  int totalSize = temp.size();
  int halfSize = totalSize / 2;

  for (int i = 0; i < halfSize; i++) {
    firstHalf.push(temp.top());
    temp.pop();
  }

  if (totalSize % 2 != 0) {
    temp.pop();
  }

  while (!temp.isEmpty()) {
    if (temp.top() != firstHalf.top()) {
      return false;
    }
    temp.pop();
    firstHalf.pop();
  }

  return true;
}


// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {

  // pushing to another stack reverses the order, so we can split in half and compare

  if (this->isEmpty()) {
    return true;
  }

  Stack<T> temp(*this);
  Stack<T> firstHalf;
  
  int totalSize = temp.size();
  int halfSize = totalSize / 2;

  for (int i = 0; i < halfSize; i++) {
    firstHalf.push(temp.top());
    temp.pop();
  }

  if (totalSize % 2 != 0) {
    temp.pop();
  }

  while (!temp.isEmpty()) {
    if (temp.top() != firstHalf.top()) {
      return false;
    }
    temp.pop();
    firstHalf.pop();
  }

  return true;
}
