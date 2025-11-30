#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {
// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implement this function
  while (!isEmpty()) {
      for (int i=0; i<source.size(); i++) {
            source.pop();
        if (i%2==0) {
            stack1.push();
        }
        else {
            stack2.push();
        }
      }
}
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
