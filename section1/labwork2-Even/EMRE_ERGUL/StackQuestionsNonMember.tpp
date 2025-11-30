#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    int counter = 1;
    while(source.isEmpty()) {
        if(counter % 2 == 1) {
            stack1.push(source.top());
            source.pop();
            counter++;
        }
        else {
            stack2.push(source.top());
            source.pop();
            counter++;
        }
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
