#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This
  
  Stack<int> stack;
  
  
  for(int i=0; i<stack.size(); i++){
  
}
  
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
  
  	Stack<int> stack;
  
  	std::vector<T> tempV;
	tempV.resize(stack.size());
	
	while (!stack.isEmpty()) {
        tempV.push_back(stack.top());
        stack.pop();
    }
    
  
}

#endif // STACK_QUESTIONS_MEMBER_TPP
