#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
// compare tops and pick smaller one, then reverse at the end
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  Stack<T> temp;
  
  while (!stack1.isEmpty() && !stack2.isEmpty()) {
    if (stack1.top() <= stack2.top()) {
      temp.push(stack1.top());
      stack1.pop();
    } else {
      temp.push(stack2.top());
      stack2.pop();
    }
  }
  
  while (!stack1.isEmpty()) {
    temp.push(stack1.top());
    stack1.pop();
  }
  
  while (!stack2.isEmpty()) {
    temp.push(stack2.top());
    stack2.pop();
  }
  
  // temp is reversed, so reverse it back
  Stack<T> result;
  while (!temp.isEmpty()) {
    result.push(temp.top());
    temp.pop();
  }
  
  return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP