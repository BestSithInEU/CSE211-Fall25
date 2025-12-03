#ifndef STACK_QUESTIONS_NON_MEMBER_H
#define STACK_QUESTIONS_NON_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace StackUtils {

/**
 * @brief Merge two sorted stacks into one sorted stack
 * @param stack1 First sorted stack (top is smallest)
 * @param stack2 Second sorted stack (top is smallest)
 * @return Merged sorted stack
 *
 * Time: O(n+m), Space: O(n+m)
 * Approach: Two-pointer merge with temporary storage
 */
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2);
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
	


/**
 * @brief Find length of longest valid parentheses substring
 * @param s String containing only '(' and ')'
 * @return Length of longest valid substring
 *
 * Time: O(n), Space: O(n)
 * Approach: Stack with index tracking
 *
 * Example: "(()" -> 2, ")()())" -> 4
 */
int longestValidParentheses(const std::string &s);
} // namespace StackUtils





while(s.isEmpty()){
	std::runtime_error("stack is empty");
}
while(!s.isEmpty()){
	for(char c: s){
		if(c == '('){
			this->push(c);
		}
		else if(c==')'){
			this->pop();
		}
	}
		
		
	}
}

// Include template implementation
#include "StackQuestionsNonMember.tpp"

#endif // STACK_QUESTIONS_NON_MEMBER_H
