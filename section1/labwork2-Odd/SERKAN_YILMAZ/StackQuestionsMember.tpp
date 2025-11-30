#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION


    StackQuestions<T> backup = *this;

    for (size_t i = 0; i < k; ++i) {

        backup.pop();

    }

    return backup.top();



}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION

    Stack<T> Stack;

    while (!empty()) {

        T current = top();

        pop();

        while (!Stack.empty() && Stack.top() > current) {

                push(Stack.top());

            Stack.pop();

        }


        Stack.push(current);

    }

    while (!Stack.empty()) {

            push(Stack.top());

                Stack.pop();

    }


}

#endif // STACK_QUESTIONS_MEMBER_TPP
