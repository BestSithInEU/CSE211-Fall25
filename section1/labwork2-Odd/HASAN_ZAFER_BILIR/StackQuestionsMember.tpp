#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  	
	count = 0;
  	Stack<T> temp;
	Stack<T> T1 = *this ;
	
	if(T1.getTop()<0){
	  return;
	}
	elif(k > size_t T1){
		std::out_of_range
		}
	
	while (count!=k){
		temp.push(T1.getTop());
		T.pop();	
	}
	
	std::cout<<T1.getTop();
	
	while(!temp.isEmtpy()){
		T1.push(temp.getTop());
		temp.pop();
	}
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
	
	Stack<T> T1 = *this;
	Stack<T> temp;
	Stack<T> temp2;
	
	while(!T1.isEmpty()){
		temp.push(T.getTop());
		T1.pop();		
	}
	
	T1.push(temp.top());
	temp.pop();
	
	while(!temp.isEmpty()){
		if(temp.getTop()<T1.top()){
			temp2.push(T1.top());
			
			T1.pop();
			T1.push(temp.getTop());
			
			T1.push(temp2.getTop());
			temp2.pop();
			temp.pop();	
		}
		
		T1.push(temp.getTop());
		temp.pop();
	}
}

#endif // STACK_QUESTIONS_MEMBER_TPP
