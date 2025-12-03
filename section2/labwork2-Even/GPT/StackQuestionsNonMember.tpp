#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils template <typename T>
void interleaveHalves(Stack<T> &stack) {
  size_t n = stack.size();
  if (n % 2 != 0 || n == 0)
    return;

  size_t half = n / 2;

  std::vector<T> first, second;
  first.reserve(half);
  second.reserve(half);

  // extract first half (topmost)
  for (size_t i = 0; i < half; i++) {
    first.push_back(stack.top());
    stack.pop();
  }

  // extract second half
  for (size_t i = 0; i < half; i++) {
    second.push_back(stack.top());
    stack.pop();
  }

  // rebuild interleaving: first[i], second[i]
  for (size_t i = 0; i < half; i++) {
    stack.push(first[i]);
    stack.push(second[i]);
  }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  size_t n = stack.size();
  std::vector<T> arr;
  arr.reserve(n);

  // convert stack to array
  while (!stack.isEmpty()) {
    arr.push_back(stack.top());
    stack.pop();
  }

  std::vector<T> nge(n, (T)-1);
  std::vector<size_t> st; // index stack

  for (size_t i = 0; i < n; i++) {
    while (!st.empty() && arr[i] > arr[st.back()]) {
      nge[st.back()] = arr[i];
      st.pop_back();
    }
    st.push_back(i);
  }

  return nge;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
