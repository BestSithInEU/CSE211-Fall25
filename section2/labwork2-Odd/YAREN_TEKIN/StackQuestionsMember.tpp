#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
	std::vector<T> arr;
    Stack<T> temp = this->stack; 
    while (!temp.isEmpty()) {
		arr.push_back(temp.top());
		temp.pop();  
	}
	int left = 0, right = arr.size() - 1;
	while (left < right) {
		if (arr[left] != arr[right]) return false;
		left++;
		right--;
	}
	return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
	template <typename T> void StackQuestions<T>::removeDuplicates() {
	std::unordered_set<T> seen;
	Stack<T> temp;
	
	while (!stack.isEmpty()) {
		T val = stack.top();
		stack.pop();
		
		if (seen.find(val) == seen.end()) {
			seen.insert(val);
			temp.push(val);
		}
	}
	while (!temp.isEmpty()) {
		stack.push(temp.top());
		temp.pop();
	}	
}
#endif // STACK_QUESTIONS_MEMBER_TPP





