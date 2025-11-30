#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  Stack<T> temp = *this;

  int length = temp.size();
  int count = 0;

  while(count < (temp.size())/2)
  {
      temp.pop();
      count++;
  }
  if(length % 2 == 0)
  {
      temp.pop();
  }

  return temp.top();
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  Stack<T> temp = *this;
  Stack<T> st;

  while(!temp.isEmpty())
  {
      st.push(temp.top());
      temp.pop();
  }

  temp = st;

}

#endif // STACK_QUESTIONS_MEMBER_TPP
