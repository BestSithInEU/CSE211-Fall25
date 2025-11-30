#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  T out;
  Stack<T> stack = *this;
  Stack<T> temp_stack;
  size_t counter = 0ULL;
  while (!stack.isEmpty())
  {
	  if (counter == k)
		  out = stack.top();
	  temp_stack.push(stack.top());
	  stack.pop();
	  counter++;
  }
  while (!temp_stack.isEmpty())
  {
	  stack.push(temp_stack.top());
	  temp_stack.pop();
  }
  return out;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  Stack<T> stack = *this;
  Stack<T> temp_stack;
  temp_stack.push(stack.top());
  stack.pop();
  T temp;
  while (!stack.isEmpty())
  {
	  if (stack.top() < temp_stack.top())
	  {
		temp = stack.top();
		stack.pop();
		while (temp_stack.top() > temp && !temp_stack.isEmpty()) {
			stack.push(temp_stack.top());
			temp_stack.pop();
		}
		temp_stack.push(temp);
		
	  }
	  else
	  {
		temp_stack.push(stack.top());
		stack.pop();
	  }
  }
  while (!temp_stack.isEmpty())
  {
	  stack.push(temp_stack.top());
	  temp_stack.pop();
  }
}


#endif // STACK_QUESTIONS_MEMBER_TPP
