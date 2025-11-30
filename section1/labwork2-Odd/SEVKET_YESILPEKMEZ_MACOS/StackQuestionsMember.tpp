#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> 
T StackQuestions<T>::getKthFromTop(size_t k) const {

    StackQuestions<T> copy = *this;
    size_t i = 0;

    if (copy.isEmpty()) {
        cout << "stack is empty" << endl;
        return T(); 
    }

    
    while (i < k) {
        if (copy.isEmpty()) {
            cout << "k is out of range" << endl;
            return T(); 
        }
        copy.pop();
        i++;
    }

    
    return copy.top();
}


// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T>
void StackQuestions<T>::sortStack() {

  Stack<T> temp; 
    
        while (!this->isEmpty()) {

        T value = this->top(); 
        this->pop();

        while (temp.top() > value) {
            this->push(temp.top());
            temp.pop();
        }

        temp.push(value);
    }

    while (!temp.isEmpty()) {
        this->push(temp.top());
        temp.pop();
    }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
