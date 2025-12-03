#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implementation
	

	Stack<T> st1 = stack1;
	Stack<T> st2 = stack2;
	
	Stack<T> temp;
	Stack<T> result;

	while(!st1.isEmpty() && !st2.isEmpty()){
		
		if(st1.getTop() <= st2.getTop()){
			temp.push(st1.getTop());
			temp.push(st2.getTop());
		}else{
			temp.push(st2.getTop());
			temp.push(st1.getTop());
		}
		
		st1.pop();
		st2.pop();
	}
	
	while(!temp.isEmpty()){
		result.push(temp.getTop());
		temp.pop();
	}

	return result;

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
