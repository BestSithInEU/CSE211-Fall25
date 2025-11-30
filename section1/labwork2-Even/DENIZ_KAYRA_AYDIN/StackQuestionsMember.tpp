#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {

  Stack<T> stack1 =*this;
  int size1;
  size1 = stack1.size();
  size1 = size1/2;
  if(stack1.isEmpty()){

  }

  for(int i = 0;i< size1;i++){
    stack1.pop();
  }
  return stack1.top();
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  Stack<T> stack2;
  Stack<T> stack3;

  while(!this->isEmpty()){
    stack2.push(this->top());
    this->pop();
  }
  while(!stack2.isEmpty()){
    stack3.push(stack2.top());
    stack2.pop();
  }
  while(!stack3.isEmpty()){
    this->push(stack3.top());
    stack3.pop();
  }

}


#endif // STACK_QUESTIONS_MEMBER_TPP
