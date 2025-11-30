#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function

  for (int size = 0; top != nullptr; size++) {
    top = top->next;
  }

  Node<T>* middle = top;
  if (size % 2 == 0) {
    for (int i = 0; i < size/2; i++) {
        middle = middle->next;
    }
  } else {
    for (int i = 1; i < size/2; i++) {
        middle = middle->next;
    }
  }
  return middle;

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
  Stack<T> temp(*this);
  while (this.top != nullptr) {
    temp.push(this.pop());
    this.top = this.top->next;
  }
   this = temp;
   delete temp;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
