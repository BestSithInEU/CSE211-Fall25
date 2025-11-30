#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  Stack<T> stack = mainStack;
  Stack<T> pot = potential;
  Stack<T> temp_stack;
  Stack<T> temp_pot;
  bool out;
  while (!stack.isEmpty())
  {
	  if (stack.top() == pot.top())
	  {
		  temp_pot.push(pot.top());
		  pot.pop();
	  }
	  temp_stack.push(stack.top());
	  stack.pop();
  }
  out = pot.isEmpty();
  while (!temp_stack.isEmpty())
  {
	  stack.push(temp_stack.top());
	  temp_stack.pop();
  }
  while (!temp_pot.isEmpty())
  {
	  pot.push(temp_pot.top());
	  temp_pot.pop();
  }
  return out;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
