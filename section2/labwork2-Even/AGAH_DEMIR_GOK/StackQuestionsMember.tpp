#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  Stack<T> snapshot(*this);
  if (snapshot.isEmpty()) {
    return 0;
  }

  std::vector<T> values;
  values.reserve(snapshot.size());
  while (!snapshot.isEmpty()) {
    values.push_back(snapshot.top());
    snapshot.pop();
  }

  size_t best = 1;
  size_t current = 1;
  const T step = static_cast<T>(1);
  for (size_t i = 1; i < values.size(); ++i) {
    const T &prev = values[i - 1];
    const T &curr = values[i];
    if (curr == prev + step || curr == prev - step) {
      ++current;
    } else {
      current = 1;
    }
    best = std::max(best, current);
  }

  return best;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  const size_t n = this->size();
  if (n <= 1) {
    return;
  }

  int mod = k % static_cast<int>(n);
  if (mod < 0) {
    mod += static_cast<int>(n);
  }
  if (mod == 0) {
    return;
  }

  Stack<T> snapshot(*this);
  std::vector<T> values;
  values.reserve(n);
  while (!snapshot.isEmpty()) {
    values.push_back(snapshot.top());
    snapshot.pop();
  }

  std::rotate(values.begin(), values.begin() + mod, values.end());

  this->clear();
  for (auto it = values.rbegin(); it != values.rend(); ++it) {
    this->push(*it);
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
