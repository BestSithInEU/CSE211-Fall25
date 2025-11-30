#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
 StackQuestions<int> stack;
stack.loadFromJSON("examples/members.json", "q2_stack");

 Stack<T> temp;
 int count = 0;
 this -> size;
 int middle = size / 2;

 while (!this->isEmpty()) {
        temp.push(this->top());
        this->pop();
        count++;
    }

for (int i = 0; i < count; i++) {
        temp.top();
        temp.pop();

        if (i == middle)
            return 3;


    }

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
 StackQuestions<int> stack;
 stack.loadFromJSON("examples/members.json", "q5_stack");

stack.reverse();
    T temp = stack.top();
    stack.pop();
    stack.push(temp);

stack.display();
while(stack != NULL){
cout << stack.top()<<endl;

}

#endif // STACK_QUESTIONS_MEMBER_TPP
