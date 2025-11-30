#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
}
a-) reverse
b-) insertAtBottom

First one:
// Reverse the stack
void reverseStack(stack<int>& st) {
    if (st.empty()) return;

    int temp = st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st, temp);

Second one:
// Insert an element to the bottom of stack
void insertAtBottom(stack<int>& , int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    int temp = st.top();
    st.pop();

    insertAtBottom(st, x);
    st.push(temp);
}

***Using temporary stack to traverse:
Stack<t>temp(this);

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
}

#endif // STACK_QUESTIONS_MEMBER_TPP
