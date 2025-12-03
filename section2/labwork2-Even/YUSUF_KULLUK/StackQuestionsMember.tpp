#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This

 if(this->isEmpty()){
        return 0;
    }
    Stack<T> temp = Stack<T>(*this);
    int tempCount;
    int ccount;
    int temp1;
    int temp2;

    while(!temp.isEmpty()){
        temp1 = temp.top();
        temp.pop();
        temp2 = temp.top();
        if((temp1-temp2 == 1) || (temp2-temp1==1)){
            tempCount++;
            if(ccount < tempCount){
                ccount = tempCount;
            }
        }
        else{
            tempCount = 0;
        }

    }
    return ccount;



}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
  int i = 0;
  int j = (this->size()+k)%this->size();
  Stack<T> temp1;
  Stack<T> temp2;


  while (i<j){
    temp1.push(this->top());
    this->pop();
  }
  while(!this->isEmpty()){
    temp2.push(this->top());
    this->pop();
  }
  while(!temp1.isEmpty()){
    this->push(temp1.top());
    temp1.pop();
  }
  while(!temp2.isEmpty()){
    this->push(temp2.top());
    temp2.pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
