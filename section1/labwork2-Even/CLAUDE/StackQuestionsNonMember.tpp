#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  while (!stack1.isEmpty()) {
    stack1.pop();
  }
  while (!stack2.isEmpty()) {
    stack2.pop();
  }

  Stack<T> temp;
  while (!source.isEmpty()) {
    temp.push(source.top());
    source.pop();
  }

  bool toStack1 = true;
  while (!temp.isEmpty()) {
    if (toStack1) {
      stack1.push(temp.top());
    } else {
      stack2.push(temp.top());
    }
    temp.pop();
    toStack1 = !toStack1;
  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
