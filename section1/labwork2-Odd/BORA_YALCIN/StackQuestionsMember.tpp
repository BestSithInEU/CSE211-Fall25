#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  /*
  store the items of the current array to another array until we reach k
  using pointers and then return k
  */
  if(k >= this.size())throw std::out_of_range;

  Stack temp = new Stack();
  Node* ptr = this.topNode;

  T item;
  T var;
  for(int i = 0;i < k;i++){
    var = ptr -> data;
    temp.push(this.push(var));
    ptr = ptr -> next;
    item = temp.top();
  }

  return item;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION

  Stack tempStack = new Stack();
  for(int i = 0;i <this.size();i++){
    Node* temp = this.topNode;
    int min =  temp -> data;
    while( temp -> next != nullptr){
        if(temp -> data  < min ){
            min =  temp -> data;
        }
        temp = temp -> next;
    }
    this.pop()
    tempStack.push(min)
    }
   this = tempStack;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
