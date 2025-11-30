#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    Stack<T> st = *this;
    Stack<T> temp;
    int n = st.size();     // 6 5 4 3 2 1       5 4 3 2 1
    int s = (n/2);    //index 0 1 2 3 4 5       0 1 2 3 4
    int i = 0;
    if(temp.isEmpty()){
            std:underflow_error;
    }
    while(i<s){
        temp.push(st.top());
        st.pop();
        i++;
    }

    return st.top();

    while(i>=0){
            st.push(temp.top());
            temp.pop();
            i--;
    }
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T> st = *this;
    Stack<T> temp1;
    Stack<T> temp2;
    while(!st.isEmpty()){
        temp1.push(st.top());
        st.pop();
    }
    while(!temp1.isEmpty()){
        temp2.push(temp1.top());
        temp1.pop();
    }
    while(!temp2.isEmpty()){
        st.push(temp2.top());
        temp2.pop();
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
