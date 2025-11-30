#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    StackQuestions<int> stack;
    stack.loadFromJSON("examples/members.json", "q2_stack");

    if (stack.isEmpty())
        return False;
    else{

    }

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    StackQuestions<int> stack;
    stack.loadFromJSON("examples/members.json", "q2_stack");

    if (stack.isEmpty())
        return False;
    else{

        stack.top();
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
