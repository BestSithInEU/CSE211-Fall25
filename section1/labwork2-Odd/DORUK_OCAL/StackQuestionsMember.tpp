#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP
#include <iostream> // i will use these.
#include <stack>
#include <string>
#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  // creating temp using the input we get (but wont for a reason :/)
}stack<int>temp = StackQuestions<int> stack;
// k must be size (i think?)
// i remove the temp stack top one by one until we get where we want
for(int i = 0;i<=k;i++){
    temp.pop();
    }
        return temp.top();



// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION


stack<int> sortStack(stack<int> &input){
    stack<int> tempoStack;
    while (!input.empty()){
        //put first temp to start the while loop
        int temp = input.top();
        input.pop();

        while (!tempoStack.empty() && tempostack.top() < temp){
            //main loop that do work
            input.push(tempoStack.top());
            tempoStack.pop();
            }

        tempoStack.push(temp);
        }
        //get the result
    return tempoStack;
    }
}




#endif // STACK_QUESTIONS_MEMBER_TPP
