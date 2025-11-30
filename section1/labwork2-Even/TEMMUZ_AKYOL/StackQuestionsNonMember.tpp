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
  int count = 1;
  while(!source.isEmpty()){

    if (count % 2 == 1){
        stack1.push(source.top());
        source.pop();
        count++;
    }
    else{
        stack2.push(source.top());
        source.pop();
        count++;
    }

  }





}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
