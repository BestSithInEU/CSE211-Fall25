#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    Stack<T>Temp(*this);
    T x = 0;
    if (this.isEmpty()) {
        std::cout<<"This stack is empty";
    }
    if (stackSize % 2 == 0){
        x = stackSize / 2;
        for (T i = 0;i<x;i++){
            Temp.pop();
        }
        return Temp.top();
    }
    if (stackSize % 2 != 0){
        x = (stackSize+1)/2;
        for (T i = 0;i<x;i++){
            Temp.pop();
        }
        return Temp.top();
    }


}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T>Temp();
    Stack<T>Temp2();
    T x = 0;
    while(!this.isEmpty()){
        x = this.top();
        Temp.push(x);
        this.pop();

    }
    while(!Temp.isEmpty()){
        x = Temp.top();
        Temp2.push(x);
        Temp.pop();

    }
    while(!Temp2.isEmpty()){
        x = Temp2.top();
        this.push(x);
        Temp2.pop();

    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
