#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  stack<int> stack1= *this;
  stack<int> temp;
  int tmp;

  for(int i=0;!stack1.empty() && i!=k,i++){
    temp.push(stack1.top());
    stack1.pop();
  }
  tmp = stack1.top();

  while(!temp.empty()){
    stack1.push(temp.top());
    temp.pop();
  }
  return tmp;


}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
  stack<int> stack1= *this;
  stack<int> temp;
  int tmp;
  while(!stack1.empty()){
      tmp=stack1.top();
      stack1.pop();
      while(!temp.empty() && temp.top()<tmp){
            stack1.push(temp.top());
            temp.pop();

      }
      temp.push(tmp);

  }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
