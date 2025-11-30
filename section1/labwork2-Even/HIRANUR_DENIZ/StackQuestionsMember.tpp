#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
  while (!isEmpty()) {
      int index = size/2;
  }
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function

  while (!isEmpty()) {
    pop();
  }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
