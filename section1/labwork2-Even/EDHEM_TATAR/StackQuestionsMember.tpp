#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
  if(this->topNode == NULL){
    return;
  }
  else{
    int n = int(this ->size());
    int middle = (n/2) + 1;
    Node<T> *current = this->topNode;

        for(int skip = 1; skip < middle; skip++){
            current = current  -> next;
        }
        return current -> data;
  }

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
  Stack<T> temp1(*this);
  Stack<T> temp2(*this);


  while(!this->isEmpty()){
    int top = int(this->top());
    this->pop();
    temp1.push(top);
  }

  while(!temp1.isEmpty()){
    int top = int(temp1.top());
    temp1.pop();
    temp2.push(top);
  }

  while(!temp2.isEmpty()){
    int top = int(temp2.top());
    temp2.pop();
    this->push(top);

  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
