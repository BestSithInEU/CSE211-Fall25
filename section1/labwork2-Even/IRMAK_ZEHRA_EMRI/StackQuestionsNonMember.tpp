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
    Stack <T> source;
    Stack <T> stack1=nullptr;
    Stack <T> stack2=nullptr;
    while(!s.isEmpty()){
            if(stack1.size()==stack2.size()){
                stack1.push(source.top());
                source.pop();
                stack2.push(source.top());
                source.pop();
            }
            source.pop();
    }
    return -1;

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
