#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  int size = this->size();
  Stack<T> temp = *this;
  int halfsize = size / 2;
    for(int i = 0; i < halfsize; i++){
        temp.push(this->pop);
    }
    T k = this->pop();
    temp.push(k);
    while(!temp.isEmpty()){
        this->push(temp.pop());
    }
    return k;

}
// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
}

#endif // STACK_QUESTIONS_MEMBER_TPP
