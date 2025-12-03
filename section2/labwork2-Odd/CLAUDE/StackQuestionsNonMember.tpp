#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  Stack<T> result;
  Stack<T> temp;

  // Merge into temp (will be in reverse sorted order)
  while (!stack1.isEmpty() && !stack2.isEmpty()) {
    if (stack1.top() >= stack2.top()) {
      temp.push(stack1.top());
      stack1.pop();
    } else {
      temp.push(stack2.top());
      stack2.pop();
    }
  }

  // Add remaining elements from stack1
  while (!stack1.isEmpty()) {
    temp.push(stack1.top());
    stack1.pop();
  }

  // Add remaining elements from stack2
  while (!stack2.isEmpty()) {
    temp.push(stack2.top());
    stack2.pop();
  }

  // Reverse temp into result to get sorted order
  while (!temp.isEmpty()) {
    result.push(temp.top());
    temp.pop();
  }

  return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
