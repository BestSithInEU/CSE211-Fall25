#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void StackUtils::splitAlternate(Stack<T> &source, Stack<T> &stack1,
                                Stack<T> &stack2) {
  stack1.clear();
  stack2.clear();

  bool toStack1 = true;

  while (!source.isEmpty()) {
    T val = source.top();
    source.pop();

    if (toStack1)
      stack1.push(val);
    else
      stack2.push(val);

    toStack1 = !toStack1;
  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
