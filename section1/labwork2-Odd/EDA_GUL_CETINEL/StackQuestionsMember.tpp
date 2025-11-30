#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
    Stack<T> temp = *this;

    for (int i = 0; i < k; i++) {
        temp.pop();
    }

    return temp.top();
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T>void StackQuestions<T>::sortStack() {
    Stack<T> temp;
    Stack<T> sorted;

    while (!this->isEmpty()) {
        temp.push(this->top());
        this->pop();
    }

    while (!temp.isEmpty()) {
        T currentMin = temp.top();
        temp.pop();

        while (!temp.isEmpty()) {
            T val = temp.top();
            temp.pop();

            if (val < currentMin) {
                this->push(currentMin);
                currentMin = val;
            } else {
                this->push(val);
            }
        }

        sorted.push(currentMin);

        while (!this->isEmpty()) {
            temp.push(this->top());
            this->pop();
        }
    }

    while (!sorted.isEmpty()) {
        this->push(sorted.top());
        sorted.pop();
    }
}



#endif // STACK_QUESTIONS_MEMBER_TPP
