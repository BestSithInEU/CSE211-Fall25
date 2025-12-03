#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implementation
  	while(!stack1.isEmpty()){
		Stack<T> sorted1;
		if(stack1.top()<stack1.pop(){
			sorted1.push(stack1.top());
			
		}
	}
		while(!stack2.isEmpty()){
		Stack<T> sorted2;
		if(stack2.top()<stac21.pop(){
			sorted2.push(stack2.top());
			
		}
	}
	
	Stack<T> mergedStack;
	
	while(!sorted1.isEmpty()) && !sorted2.isEmpty()){
		if(stack1.pop()<stack2.pop()){
			mergedStack.push(stack1.pop());
			
		}
		else {
			mergedStack.push(stacj2.pop());
		}
	}
	
	return mergedStack;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
