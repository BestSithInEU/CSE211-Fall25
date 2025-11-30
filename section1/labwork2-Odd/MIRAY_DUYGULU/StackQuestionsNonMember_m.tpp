#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // TODO: IMPLEMENTATION


  while(!mainStack.empty()){
      if(potential.top()!=mainStack.top()){
        mainStack.pop();
      }
      mainstack.pop();
      potential.pop();
      if (potential.size()==1 && potential.top()==mainStack.top()){
        return true;
      }
  }
  return false;


}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
