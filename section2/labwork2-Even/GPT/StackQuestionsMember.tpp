#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  if (stack.isEmpty())
    return 0;

  Stack<T> temp = stack;
  size_t best = 1;
  size_t curr = 1;

  T prev = temp.top();
  temp.pop();

  while (!temp.isEmpty()) {
    T now = temp.top();
    temp.pop();

    if (now + 1 == prev) {
      curr++;
    } else {
      best = std::max(best, curr);
      curr = 1;
    }
    prev = now;
  }

  best = std::max(best, curr);
  return best;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  size_t n = stack.size();
  if (n == 0)
    return;

  k = ((k % (int)n) + n) % n; // normalize
  if (k == 0)
    return;

  std::vector<T> v;
  v.reserve(n);

  while (!stack.isEmpty()) {
    v.push_back(stack.top());
    stack.pop();
  }
  // now v[0] = old top

  // rotate right by k â†’ index moves to (i+k)%n
  std::rotate(v.begin(), v.begin() + (n - k), v.end());

  // push back to stack
  for (auto &x : v)
    stack.push(x);
}

#endif // STACK_QUESTIONS_MEMBER_TPP
