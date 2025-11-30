#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  if (k >= this->size()){
    throw std::out_of_range("Index out of range");
  }

  Stack<T> temp;
  size_t count = 0;
  T result;

  while (count <= i) {
    T val = this->top();
    temp.push(val);

    this->pop();
    if (count == i) {
      result = val;
    }
    count++;
  }

  while (!temp.isEmpty()) {
    this->push(temp.top());
    temp.pop();
  }

  return result;
  }

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack(){

  Stack<T> temp;

  while (!this->isEmpty()){
    T current = this->top();
    this->pop();

    while (!temp.isEmpty()){
      this->push(temp.top());
      temp.pop();
    }
    temp.push(current);
  }

  while (!temp.isEmpty()){
    this->push(temp.top());
    temp.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
