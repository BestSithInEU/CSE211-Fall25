#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence(){

	Stack<int> stack;	
	if(stack.isEmpty()) return 0;
	if(stack.size()==1) return 1;
	
	int count=0;
	int tempfront= stack.pop();
	int tempsecond= stack.pop();
	int tempcount=0;
	
	while(stack.isEmpty()){
			if(tempcount>count) count=tempcount;
		while(tempfront+1==tempsecond){
			tempfront=tempsecond;
			tempsecond=stack.pop();
			tempcount++;
		}
	}
		
	
	return count;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // 
  	
  	Stack<int> stack;
  	if (!stack.isEmpty()) return;
  	int size =stack.size();
  	Stack<int> tempstack;
	
	if (k>0){
		for(int i=0; i<k; i++){
			tempstack.push(stack.pop());
		}
		while(tempstack.isEmpty()){
			stack.push(tempstack.pop());
		}
	}else{
		for(int i=0; (i<size+k); i++){
			tempstack.push(stack.pop());
		}
		while(tempstack.isEmpty()){
			stack.push(tempstack.pop());
		}	
	}
}

#endif // STACK_QUESTIONS_MEMBER_TPP
