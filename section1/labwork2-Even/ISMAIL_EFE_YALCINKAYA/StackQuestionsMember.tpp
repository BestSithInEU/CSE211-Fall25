#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() {
    std::size_t n = this->size(n);
    if (n == 0) {
        throw std::error("Stack empty");
    } else {
        throw std::cout << "Stack is not empty";
    }
    size_t midNum= n / 2;
    return this->Top(midNum);
}
// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    StackQuestions<T> temp;
    while (!isEmpty()) {
        temp.push(this->pop());
    }
    while (!temp.isEmpty()) {
        this->push(temp.pop());
    }
}
#endif // STACK_QUESTIONS_MEMBER_TPP
