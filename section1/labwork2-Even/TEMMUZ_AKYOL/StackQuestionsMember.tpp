#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
  if (this->isEmpty()) {
    throw std::underflow_error("Stack is empty");
  }

  Stack<T> temp = *this;
  int n = temp.size();
  int mid = n/2;

  for (int i = 0; i < mid; ++i) {
    temp.pop();
  }

  return temp.top();

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
  if(this->isEmpty()){
    return;
  }
  Stack<T> temp1;
  while(!this->isEmpty()){
    temp1.push(this.top());
    this.pop();
  }

  Stack<T> temp2;
  while(!temp1.isEmpty()){
    temp2.push(temp1.top());
    temp1.pop();
  }

  while(!temp2.isEmpty()){
    this->push(temp2.top());
    temp2.pop();
  }






}

#endif // STACK_QUESTIONS_MEMBER_TPP
