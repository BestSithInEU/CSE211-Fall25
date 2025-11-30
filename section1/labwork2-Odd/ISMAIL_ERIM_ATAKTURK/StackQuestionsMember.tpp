#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  if (k == 0 || k > this->size()) {
    throw std::out_of_range("k is out of range")
  }
  StackQuestions<T> temp(*this);

  for(size_t i = 1; i < k; ++i){
    tmp.pop();
  }

  return tmp.top();
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {

  StackQuestions<T> tmp;

  while (!this->empty()) {
    T x = this->top();
    this->pop();

        while (!tmp.empty()&& tmp.top() > x) {
            this->push(tmp.top());
        }
        tmp.push(x);
  }

  while (!tmp.empty()) {
    this->push(tmp.top());
    tmp.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
