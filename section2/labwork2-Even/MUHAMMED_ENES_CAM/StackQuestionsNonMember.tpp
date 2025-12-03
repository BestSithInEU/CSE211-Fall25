#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
// TODO: Implement This

template <typename T> void interleaveHalves(Stack<T>& stack){
	
	
	int stack_size = stack.size();
	
	Stack<T> bottom_Half;
	Stack<T> top_Half;
	
	int bot_size = stack.size()/2;
	
	for(int i=0; i<bot_size ; i++){		
		bottom_Half.push(stack.top());
		stack.pop();		
	}
	
	for (; !stack.isEmpty(); stack.pop()) {
    	top_Half.push(stack.top());
	}	
	
		
	while (!bottom_Half.isEmpty()) {
        
		stack.push(top_Half.top());
        top_Half.pop();
        
        stack.push(bottom_Half.top());
        bottom_Half.pop();
    }
	
	
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
  
	Stack<T> stack2;
	
	std::vector<T> result;
	
	while(!stack.isEmpty()){	
		stack2.push(stack.top());
		stack.pop();
	}
	
	int main_size = stack2.size();
	
	std::vector<T> elements;
	elements.resize(main_size);
	
	while (!stack2.isEmpty()) {
        elements.push_back(stack2.top());
        stack2.pop();
    }
    
    int el_Size = elements.size();
  	
  	for (int i = 0; i < el_Size; ++i) {
  
        	T currentElement = elements[i];
        	T nextGreater = T(-1); 

        	for (int j = i + 1; j < el_Size; ++j) {
            	
				T rightElement = elements[j];
                      
            	if (rightElement > currentElement) {
                	nextGreater = rightElement;
                	break; 
            	}
        	}
  
  			result.push_back(nextGreater);
  
  }
  
  return result;
  
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
