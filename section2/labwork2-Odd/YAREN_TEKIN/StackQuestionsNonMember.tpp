#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  
}

	Stack<T> c1 = s1, c2 = s2;
	std::vector<T> a, b;
	
	while (!c1.isEmpty()) { a.push_back(c1.top()); c1.pop(); }
	while (!c2.isEmpty()) { b.push_back(c2.top()); c2.pop(); }
	
	std::vector<T> merged;
	int i = 0, j = 0;
	
	while (i < a.size() && j < b.size()) {
		if (a[i] < b[j]) merged.push_back(a[i++]);
		else merged.push_back(b[j++]);
	}
	
	while (i < a.size()) merged.push_back(a[i++]);
	while (j < b.size()) merged.push_back(b[j++]);
	
	Stack<T> result;
	for (int k = merged.size() - 1; k >= 0; k--)
		result.push(merged[k]);
		
	return result;
}
#endif // STACK_QUESTIONS_MEMBER_TPP





