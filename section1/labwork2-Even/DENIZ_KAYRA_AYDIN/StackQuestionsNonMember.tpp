#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    Stack<T> temp1;
    bool sira = true;
    while(!source.isEmpty()){
        temp1.push(source.top());
        source.pop();
    }
    while(!temp1.isEmpty()){
    if(sira){
        stack1.push(temp1.top());
    }
    else{
        stack2.push(temp1.top());
    }
    temp1.pop();
    sira = !sira;
    }

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
