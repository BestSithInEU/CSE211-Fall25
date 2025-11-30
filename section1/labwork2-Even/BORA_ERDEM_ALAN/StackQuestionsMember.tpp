#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
  int n;
  Stack<T> temp1(*this);
  Stack<T> temp2;
  n = temp1.size();

  for(int i = 0; i <= n/2; i++){
    temp2.push(temp1.top());
    temp1.pop();
  }
  int mid = temp2.top();
  return mid;
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
  Stack<T> temp1(*this);
  Stack<T> temp2;
  Stack<T> temp3;
  while(!temp1.isEmpty()){
    temp2.push(temp1.top());
    temp1.pop();
  }
  while(!temp2.isEmpty()){
    temp3.push(temp2.top());
    temp2.pop();
  }
  while(!temp3.isEmpty()){
    temp1.push(temp3.top());
    temp3.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
