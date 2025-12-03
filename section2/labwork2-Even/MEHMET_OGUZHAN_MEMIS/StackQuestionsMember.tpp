#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This
  StackQuestions<int> stack = *this;
  if(stack.isEmpty()){
    return 0;
  }
  stack.display();
  int count = 1;
  int a;
  int max = 1;
  while(!stack.isEmpty()){
    a = stack.top();
    stack.pop();
    if (a + 1 == stack.top() || a - 1 == stack.top()){
        count++;
    }else{
        if (count > max){
            max = count;
        }
        count = 1;
    }
  }
  return max;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
}

#endif // STACK_QUESTIONS_MEMBER_TPP
