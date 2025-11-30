#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  Stack<T> c =*this;
  if(k>size()) return;
  //Node* temp=topNode;
  int i=0;
  for(;i<k;i++){
    c.pop();
  }
  return c.top();
  //return temp->data;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
  Stack<T> temp;
  while(!isEmpty()){
    T cur;
    cur=top();
    pop();
    while(!temp.isEmpty()&&(temp->top()>cur){
        push(temp->top());
        temp->pop();
    }
    temp->(push(cur));
  }
  while(!temp.isEmpty()){
    push(temp->top());
    temp->pop();
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
