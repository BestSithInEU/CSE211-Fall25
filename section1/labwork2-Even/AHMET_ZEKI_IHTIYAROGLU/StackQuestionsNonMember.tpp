#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    T counter = 0;
    T num = 0;
    T sizee = source.stackSize;
    while (source.stackSize != 0){
        for(T i = 0; i < sizee; i++){
            num = source.top();
            if (counter%2 == 0){
                stack1.push(num);
            }
            else{
                stack2.push(num);
            }
            source.pop();
            counter = counter + 1;
        }
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
