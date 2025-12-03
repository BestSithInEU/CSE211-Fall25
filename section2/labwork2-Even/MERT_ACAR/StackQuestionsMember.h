#ifndef STACK_QUESTIONS_MEMBER_H
#define STACK_QUESTIONS_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T> class Stack; // Forward declaration

// Extend Stack with additional member functions
template <typename T> class StackQuestions : public Stack<T> {
public:
  using Stack<T>::Stack; // Inherit constructors

  // ============================================================================
  // Question 1: Longest Consecutive Subsequence
  // ============================================================================
  
  template <typename T>
  size_t StackQuestions<T>::longestConsecutiveSequence() const {
  	if (this->empty())
  		return 0;
  		
  	Stack<T> copy = *this;
  	Stack<T> temp;
  	
  	while (!copy.empty()) {
  		temp.push(copy.top());
  		copy.pop();
	  }
	  
	T prev = temp.top();
	temp.pop();
	
	size_t longest = 1;
	size_t current = 1;
	
	while (!temp.empty()) {
		T x = temp.top();
		temp.pop();
		
		if (x == prev + 1) {
			current++;
		} else {
			current = 1;
		}
		
		longest = std::max(longest, current);
		prev = x;
	}
	
	return longest;
  }
  size_t longestConsecutiveSequence() const;

  // ============================================================================
  // Question 2: Rotate Stack
  // ============================================================================
  template <typename T>
  void StackQuestions<T>::rotateStack(int k) {
  	if (this->empty())
  		return;
  		
	Stack<T> temp1;
	Stack<T> temp2;
	
	int n = 0;
	
	Stack<T> copy = *this;
	while (!copy.empty()) {
		temp1.push(copy.top());
		copy.pop();
		n++;
	}
	
	k = k % n;
	if (k == 0) {
		return;
	}
	
	for (int i = 0; i < k; i++) {
		temp2.push(temp1.top());
		temp1.pop();
	}
	
	Stack<T>::clear();
	
	while (!temp2.empty()) {
		this->push(temp2.top());
		temp2.pop();
	}
	
	while (!temp1.empty()) {
		this->push(temp1.top());
		temp1.pop();
	}
		
  }

  void rotateStack(int k);
};

// Include template implementation
#include "StackQuestionsMember.tpp"

#endif // STACK_QUESTIONS_MEMBER_H
