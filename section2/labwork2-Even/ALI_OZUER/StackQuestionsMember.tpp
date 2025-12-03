#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  if (*this.isEmpty())
    return 0;
  if (*this.size() == 1)
    return 1;
  Stack<T> st = *this;
  Stack<T> temp;
  int prev = st.top();
  st.pop();
  int cur = 1;
  int max = 0;
  while (!st.isEmpty()) {
    if (st.top() + 1 == prev) {
      cur++;
      prev = st.top();
      st.pop();
    } else {
      cur = 1;
      prev = st.top();
      st.pop();
    }
    if (cur > max)
      max = cur;
  }
  return max;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  if (*this.size() <= 1 || k == 0)
    return;
  Stack<T> temp1;
  Stack<T> temp2;
  k = k % *this.size();
  if (k > 0) {
    for (int i = 0; i < k; i++) {
      temp1.push(*this.top());
      *this.pop();
    }
    while (!*this.isEmpty()) {
      temp2.push(*this.top());
      *this.pop();
    }
    while (!temp1.isEmpty()) {
      *this.push(temp1.top());
      temp1.pop();
    }
    while (!temp2.isEmpty()) {
      *this.push(temp2.top());
      temp2.pop();
    }
  } else {
    for (int i = 0; i > k; i--) {
      temp2.push(*this.top());
      *this.pop();
    }
    while (!*this.isEmpty()) {
      temp1.push(*this.top());
      *this.pop();
    }
    while (!temp2.isEmpty()) {
      *this.push(temp1.top());
      temp2.pop();
    }
    while (!temp1.isEmpty()) {
      *this.push(temp2.top());
      temp1.pop();
    }
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
