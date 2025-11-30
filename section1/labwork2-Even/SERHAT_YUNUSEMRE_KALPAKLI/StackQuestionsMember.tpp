#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    Stack<T> temp=*this;
    size_t middle=temp.size()/2;
  if(!temp.isEmpty()){
    for(size_t i=0;i<middle;i++){
        temp.pop();
    }
    return temp.top();
  }
  //else{throw std::underflow_error;}//Only else remains
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T> temp;//Eksik
    size_t k;
   size_t a;
   for(size_t i=0;i<this->size();i++){
       k=this->top();
       this->pop();
        while(!this->isEmpty()){
        a=this->top();
        this->pop();
        temp.push(a);
        }
        this->push(k);
        while(!temp.isEmpty()){
        a=temp.top();
        temp.pop();
        this->push(a);
        }
    }
    //Not yet
}

#endif // STACK_QUESTIONS_MEMBER_TPP
