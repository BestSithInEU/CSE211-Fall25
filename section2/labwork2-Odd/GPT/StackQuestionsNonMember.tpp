#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  Stack<T> result;

  while (!s1.empty() || !s2.empty()) {
    if (s1.empty()) {
      result.push(s2.top());
      s2.pop();
    } else if (s2.empty()) {
      result.push(s1.top());
      s1.pop();
    } else if (s1.top() < s2.top()) {
      result.push(s1.top());
      s1.pop();
    } else {
      result.push(s2.top());
      s2.pop();
    }
  }

  // Reverse to get ascending w/ top = smallest
  Stack<T> finalStack;
  while (!result.empty()) {
    finalStack.push(result.top());
    result.pop();
  }
  return finalStack;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
