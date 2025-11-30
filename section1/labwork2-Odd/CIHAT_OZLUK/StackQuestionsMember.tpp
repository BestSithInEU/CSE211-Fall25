#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP
#include <iostream>
#define SIZE 10
#include "StackQuestionsMember.h"
using namesapce std;

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================

struct stack{
    int data[SIZE];
    int top=-1;
};


template <typename T> T StackQuestions<T>::getKthFromTop(stack stk,size_t k) const {
    if(k>=SIZE){
        throw "out_of_range";
    }
    else
    {
        return stk.data[top-k]
    }

}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
}

#endif // STACK_QUESTIONS_MEMBER_TPP
