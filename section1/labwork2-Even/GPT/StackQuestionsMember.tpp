#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  if (this->isEmpty())
    throw std::underflow_error("Stack is empty");

  size_t n = this->size();
  size_t mid = n / 2; // lower-middle for even, correct for odd

  return this->getKthFromTop(mid);
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T>
void insertAtBottom(StackQuestions<T> &st, const T &value) {
  if (st.isEmpty()) {
    st.push(value);
    return;
  }
  T topVal = st.top();
  st.pop();
  insertAtBottom(st, value);
  st.push(topVal);
}

template <typename T> void StackQuestions<T>::reverse() {
  if (this->isEmpty())
    return;

  T topElem = this->top();
  this->pop();

  reverse();                      // reverse remaining
  insertAtBottom(*this, topElem); // place popped at bottom
}

#endif // STACK_QUESTIONS_MEMBER_TPP
