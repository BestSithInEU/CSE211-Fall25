#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION

    Stack<T> temp = *this;

    for (size_t i = 0; i < k; ++i) {
        temp.pop();
    }

    return temp.top();
}




// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION


    Stack<T> temp;

    while (!this->empty()) {
        T current = this->top();
        this->pop();



  }

}

#endif // STACK_QUESTIONS_MEMBER_TPP





























