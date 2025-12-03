#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  Stack<T> copy1 = stack1;
  Stack<T> copy2 = stack2;
  Stack<T> mergedTempStack;
  Stack<T> finalMergedStack;
 
  if (copy1.top() <= copy2.top()) {
      mergedTempStack.push(copy1.top());
      copy1.pop();
    } else {
      mergedTempStack.push(copy2.top());
      copy2.pop();
    }
  
  while (copy1.size()>0) {
    mergedTempStack.push(copy1.top());
    copy1.pop();
  }

  while (copy2.size()>0) {
    mergedTempStack.push(copy2.top());
    copy2.pop();
  }
  while (mergedTempStack.size()>0) {
    finalMergedStack.push(mergedTempStack.top());
    mergedTempStack.pop();
  }
    return finalMergedStack;
  
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
