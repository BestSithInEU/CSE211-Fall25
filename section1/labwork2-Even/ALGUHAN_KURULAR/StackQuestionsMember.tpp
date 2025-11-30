#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
	if(this->isEmpty()){
        throw std::underflow_error();
	}

	int mid = this->size() / 2;


	Stack<T> cur = *this;

	for(int i = 0; i < mid; i++){
        cur = cur->next;
	}

	return cur->data;

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {

  Stack<T> temp ;
  Stack<T> temp2;

  while(!this->isEmpty()){
    int val = this->pop();
    temp.push(val);
  }

  while(!temp.isEmpty()){
    int val = temp.pop();
    temp2.push(val);
  }

  delete temp;

  while(!temp2.isEmpty()){
    int val = temp2.pop();
    this->push(val);
  }

delete temp2;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
