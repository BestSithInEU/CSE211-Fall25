#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  std::stack<T>mainCopy = mainStack.stack;
  std::stack<T>potCopy = potential.stack;
  if(potCopy.empty())
    return true;
  T target = potCopy.top();
  potCopy.pop();

  while(!mainCopy.empty()) {
    if(mainCopy.top() == target) {
        if(potCopy.empty())
            return true;
        taget == potCopy.top();
        potCopy.pop();
    }
    mainCopy.pop();
  }

  return false;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
