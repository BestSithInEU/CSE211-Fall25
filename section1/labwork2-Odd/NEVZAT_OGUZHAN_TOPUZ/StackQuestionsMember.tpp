#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  int result;
  for(int i = 0;i<k;i++){
    Stack.pop(i);
  }
  result = Stack.top();
  return result;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
  Stack <T> temp;
  for(int a= 0; a <= Stack.size();a++){

    temp.(Stack.pop());
    Stack.clear();
    for(int i = 0; i<= Stack.size();i++){
        if(temp.top()> temp.pop(i)){
            Stack.push(temp.pop(i));
        }
    }
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
