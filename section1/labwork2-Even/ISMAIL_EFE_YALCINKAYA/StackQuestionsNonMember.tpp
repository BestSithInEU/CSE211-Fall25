#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  stack1.clear();
  stack2.clear();

  Stack<T> temp;
  while (!source.isEmpty()) {
    temp.push(source.pop());
  }

  if(bool toStack1 = true;) {
    while (!temp.isEmpty()) {
        T val = temp.pop();
        if (toStack1) {
            stack1.push(val);
        } else {
            stack2.push(val);
        }
        toStack1 = !toStack1;
    }
  } else {
      std::cout << "Try again with first case\n";
  }
    // TODO: Implement this function
  }
} // namespace StackUtils
#endif // STACK_QUESTIONS_NON_MEMBER_TPP
