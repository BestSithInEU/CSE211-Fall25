#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  // TODO: Implementation
	
	if(stack.isEmpty()) return true;

	Stack<T> st_copy = stack;
	Stack<T> temp ;
	
	while(!st_copy.isEmpty()){
		temp.push(st_copy.getTop());
		st_copy.pop();
	}
	
	Stack<T> st_copy2 = stack;

	while(!st_copy2.isEmpty() && !temp.isEmpty()){
		if(st_copy2.getTop() != temp.getTop()){
			return false;
		}
		st_copy2.pop();
		temp.pop();
	}

	return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
  // TODO: Implementation

	Stack<T> onlyOne;
	Stack<T> checker;

	while(!stack.isEmpty()){
		T val = stack.getTop();
		stack.pop();
	
	
		bool alreadyExists = false;
		while(!onlyOne.isEmpty()){
			T val2 = onlyOne.getTop();
			onlyOne.pop();

			if(val2 == val){
				alreadyExists = True;
			}
			checker.push(val2);
		}

		while(!checker.isEmpty()){
			onlyOne.push(checker.getTop());
			checker.pop();
		}
		if(!alreadyExists){
			onlyOne.push(val);
		}

	}
	while(!onlyOne.isEmpty()){
		stack.push(onlyOne.getTop());
		onlyOne.pop();
	}


}

#endif // STACK_QUESTIONS_MEMBER_TPP
