#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    source.loadFromJSON("examples/nonmembers.json", "q13_stack")


    while (!stack1.isEmpty()){
            stack1.pop();
    }
    while (!stack2.isEmpty()){
            stack2.pop();
    }

    Stack<int> stack1, stack2;
    StackUtils::splitAlternate(source, stack1, stack2);

        if (temp.isEmpty()){
            stack1.push(temp.top());
        }
        else{
            stack2.push(temp.top());
            ]

        temp.pop();

    }
}
#endif
