#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    bool alt=true;
  while(!source.isEmpty()){
    if(alt){stack1.push(source.top());//Done
    source.pop();
    alt=false;}
    else{
    stack2.push(source.top());
    source.pop();
    alt=true;}

  }

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
