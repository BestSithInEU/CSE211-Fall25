#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack) {
  const size_t n = stack.size();
  if (n <= 1) {
    return;
  }

  Stack<T> snapshot(stack);
  std::vector<T> topToBottom;
  topToBottom.reserve(n);
  while (!snapshot.isEmpty()) {
    topToBottom.push_back(snapshot.top());
    snapshot.pop();
  }

  std::vector<T> bottomFirst(topToBottom.rbegin(), topToBottom.rend());

  const size_t bottomSize = (n + 1) / 2;
  const size_t topSize = n - bottomSize;

  std::vector<T> interleaved;
  interleaved.reserve(n);
  for (size_t i = 0; i < bottomSize; ++i) {
    interleaved.push_back(bottomFirst[i]);
    if (i < topSize) {
      interleaved.push_back(bottomFirst[bottomSize + i]);
    }
  }

  stack.clear();
  for (auto it = interleaved.rbegin(); it != interleaved.rend(); ++it) {
    stack.push(*it);
  }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  std::vector<T> topToBottom;
  topToBottom.reserve(stack.size());
  while (!stack.isEmpty()) {
    topToBottom.push_back(stack.top());
    stack.pop();
  }

  if (topToBottom.empty()) {
    return {};
  }

  std::reverse(topToBottom.begin(), topToBottom.end()); // bottom to top

  const size_t n = topToBottom.size();
  const T sentinel = static_cast<T>(-1);
  std::vector<T> result(n, sentinel);
  std::vector<T> mono;
  mono.reserve(n);

  for (size_t idx = n; idx-- > 0;) {
    const T current = topToBottom[idx];
    while (!mono.empty() && mono.back() <= current) {
      mono.pop_back();
    }
    if (!mono.empty()) {
      result[idx] = mono.back();
    }
    mono.push_back(current);
  }

  return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
