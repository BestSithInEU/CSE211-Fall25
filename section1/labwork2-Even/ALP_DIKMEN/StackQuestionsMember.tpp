#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function

  Stack<T> copystack=*this;
  int n=copystack.size();
  n=n/2;

  for(int i=0;i<n;i++)
  {
      copystack.pop();
  }

  return copystack.top();
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
  Stack<T> tempstack;
  Stack<T> tempstack2;

  while(!this->isEmpty())
  {
      tempstack.push(this->top());
      this->pop();
  }

    while(!tempstack.isEmpty())
  {
      tempstack2.push(tempstack.top());
      tempstack.pop();
  }

    while(!tempstack2.isEmpty())
  {
      this->push(tempstack2.top());
      tempstack2.pop();
  }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
