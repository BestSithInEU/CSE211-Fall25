#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  Stack<T> stack2;
  		
  		if(this->isEmpty()){
  			return true;//stack is empty;
		  }
		
		else{
			while(!this->isEmpty()){
				stack2.push(pop());//stack2 is reversed array
				this->pop();
			}
			
			while(!this->isEmpty()&& !stack2.isEmpty()){
				if(this->pop()==stack2.pop()){
					return true;//palindrome 
				}
				return false;
				// not palindrome 
			}
			
			
		}
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
Stack<T> tempStack;
  	
  	std::set<T> tempStack;
  	
  	
  	while(!this->isEmpty()){
  		this->pop();
  		while(!tempStack.empty()){
  			this->push(tempStack.erase());//erase() holds the top element int the temp stack;
		  }
  		
  		
  		
  		
	  }
  
 	return Stack<T>;//no duplicates in the original array anymore}

#endif // STACK_QUESTIONS_MEMBER_TPP
