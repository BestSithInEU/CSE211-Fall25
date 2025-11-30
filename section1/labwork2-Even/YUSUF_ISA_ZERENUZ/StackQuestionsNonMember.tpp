#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  int count = 2;
  while(!source.isEmpty()){
        if(count % 2 = 0){
            stack1.push(source.top());
            source.pop();
        }else {
            stack2.push(source.top());
            source.pop();
        }
        count++;
  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
