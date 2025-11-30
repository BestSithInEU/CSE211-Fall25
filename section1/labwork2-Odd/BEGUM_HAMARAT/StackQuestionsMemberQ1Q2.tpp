#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================

template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
    if(k>=this -> stack.size()) {
        throw std :: out_of_range("k is out of range");
    }

    std::stack <T>copy = this -> stack;

    for(size_t i=0 ; i<k ; ++i){
        copy.pop();
    }

  return copy.top();
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  std::stack<T> temp;

  while(!this -> stack.empty()) {
    T cur = this -> stack.top();
    this-> stack.pop();

    while(!temp.empty()&& temp.top() < cur) {
        this-> stack.push(temp.top());
        temp.pop();
    }

    temp.push(cur);
  }

  this -> stack.swap(temp);
}

#endif // STACK_QUESTIONS_MEMBER_TPP
