#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack){
	
	Stack<int> topstack;
	Stack<int> bottomstack;
	
	int mid = ((stack.size()+1)/2);
	
	if(stack.size()%2==0){
		while(mid>0){
			topstack.push(stack.pop());// i intended to use stack.pop as the value that 
		}							   // it returns
		while(stack.isEmpty()){
			bottomstack.push(stack.pop());
		}
	}else{
		while(mid>1){
			topstack.push(stack.pop());
		}
		while(stack.isEmpty()){
			bottomstack.push(stack.pop());
		}
	}
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> void nextGreaterElement(Stack<T> stack) {
  	
  	int arraySize = stack.size();
  	int array[arraySize];
  	for(int i=0; i<arraySize; i++){
		array[i]=stack.pop();
	}
	
	for(int i=0; i<arraySize; i++){
		int max= array[i];
		for(int j=1; i<arraySize; j++){
			if(array[j]>max) max= array[j];
		}
		if(max!= array[i]){
			std::cout << max << "  " << "\n";
		}else{
			std::cout << -1 << "  " << "\n";
		}
	}


} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
