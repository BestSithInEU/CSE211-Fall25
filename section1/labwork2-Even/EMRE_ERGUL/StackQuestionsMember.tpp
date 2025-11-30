#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    Stack<T> temp = *this;
    Stack<T> current;
    int counter = 0;
    while(!temp.isEmpty()) {
        current.push(temp.top());
        temp.pop();
        counter++;
    }
    while(!current.isEmpty()) {
        temp.push(current.top());
        current.pop();
    }
    int mid = 0;
    if (counter % 2 == 1) {
        mid = (temp.size() / 2) + 1;
    }
    else {
        mid = (temp.size() / 2);
    }
    for(int i = 1; i < mid; i++) {
        current.push(temp.top());
        temp.pop();
    }
    return temp.top();
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T> temp = *this;
    Stack<T> current;
    while(!temp.isEmpty()) {
        current.push(temp.top());
        temp.pop();
    }
    this = current;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
