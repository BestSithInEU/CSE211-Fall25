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
}
using
template <typename T>
2 void splitAlternate(Stack<T>& source, Stack<T>& stack1, Stack<T>& stack2)
Stack<int> source; source.loadFromJStack("majorstack");
// Source (top to bottom): 9,8,7,6,5,4,3

Stack<int> stack1, stack2;
StackUtils::splitAlternate(source, stack1, stack2);
// stack1 (top to bottom): 9,8,7,6
8 // stack2 (top to bottom): 5,4,3
9 // source stack is empty rn

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
