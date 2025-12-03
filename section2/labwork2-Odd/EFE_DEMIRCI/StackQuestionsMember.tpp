#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  // TODO: Implementation
	if(this->isEmpty()){
	
	return true;
	}
	
	Stack<T> temp;
	Stack<T> temp_reverse;
	
	temp = *this;
	
	while(!temp.isEmpty()){
	temp_reverse.push(temp.top());
	temp.pop();
	
	}
	temp = *this;
	
	while(!temp.isEmpty()){
	
		if(temp.top()!=temp_reverse.top()){
			return false;
		}
		temp.pop();
		temp_reverse.pop();
	
	}
	return true;
  
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T>
void StackQuestions<T>::removeDuplicates() {
    std::vector<T> uniqueItems;

    while (!this->isEmpty()) {
        T current = this->top();
        this->pop();

        bool isDuplicate = false;
        for (size_t i = 0; i < uniqueItems.size(); ++i) {
            if (uniqueItems[i] == current) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            uniqueItems.push_back(current);
        }
    }

    for (int i = uniqueItems.size() - 1; i >= 0; --i) {
        this->push(uniqueItems[i]);
    }
}
  
  
  
  
  
  
  
  }

#endif // STACK_QUESTIONS_MEMBER_TPP



























