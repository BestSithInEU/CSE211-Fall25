#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  if (this->isEmpty()) {
    throw std::underflow_error("Stack is empty");
  }

  int n = this->size();
  int middlePos = n / 2;

  StackQuestions<T> temp;
  StackQuestions<T>* self = const_cast<StackQuestions<T>*>(this);

  for (int i = 0; i < middlePos; i++) {
    temp.push(self->top());
    self->pop();
  }

  T middleElem = self->top();

  while (!temp.isEmpty()) {
    self->push(temp.top());
    temp.pop();
  }

  return middleElem;
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  if (this->isEmpty()) {
    return;
  }

  T topElem = this->top();
  this->pop();

  reverse();

  insertAtBottom(topElem);
}

template <typename T> void StackQuestions<T>::insertAtBottom(const T& item) {
  if (this->isEmpty()) {
    this->push(item);
    return;
  }

  T topElem = this->top();
  this->pop();

  insertAtBottom(item);

  this->push(topElem);
}

#endif // STACK_QUESTIONS_MEMBER_TPP
