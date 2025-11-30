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

  int oe=0;
  while(!source.isEmpty())
  {
      if(oe==0)
      {
          stack1.push(source.top());
          oe=1;
      }
      else
      {
          stack2.push(source.top());
          oe=0;
      }

      source.pop();

  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
