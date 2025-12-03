#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleavesHalves(Stack<T> stack) {
	
	if(stack.isEmpty())
	{
		return;
	}
	
	Stack<T> topHalf;
	Stack<T> bottomHalf;
	
	int topHalfPush = (stack.size()) / 2; // for top half push counter
	
	int counter = 0;
	while(stack.isEmpty())
	{
		if(counter < topHalf)
		{
			topHalf.push(stack.top());
			stack.pop();
			counter++;
		}
		else{
			bottomHalf.push(stack.top());
			stack.pop();
		}
	}
	
	//for alternating part
	while(!bottomHalf.isEmpty())
	{
		if(!bottomHalf.isEmpty())
		{
			stack.push(bottomHalf.top());
			bottomHalf.pop();
		}
		
		if(!topHalf.isEmpty())
		{
			stack.push(bottomHalf.top());
			bottomHalf.pop();
		}
	}
	
	
	//to reverse i will use both stack
	while (!stack.isEmpty()) {
        topHalf.push(stack.top());
        stack.pop();
    }

    while (!topHalf.isEmpty()) {
        bottomHalf.push(topHalf.top());
        topHalf.pop();
    }

    while (!bottomHalf.isEmpty()) {
        stack.push(bottomHalf.top());
        bottomHalf.pop();
    }
}
		
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T>
std::vector<T> nextGreaterElement(Stack<T> stack) {
    std::vector<T> result;
    
    if (stack.isEmpty()) {
        return result;
    }

    Stack<T> tempStack;
    while (!stack.isEmpty()) {
        tempStack.push(stack.top());
        stack.pop();
    }
	
	//filling myVector
    std::vector<T> myVec;
    while (!tempStack.isEmpty()) {
        myVec.push_back(tempStack.top());
        tempStack.pop();
    }

    int n = myVec.size();
    
    // Fill result with -1
    for(int i = 0; i < n; i++) {
        result.push_back(-1);
    }
    
    std::stack<T> helperStack;

    for (int i = n - 1; i >= 0; i--) {
        T currentVal = myVec[i];

        while (!helperStack.empty() && helperStack.top() <= currentVal) {
            helperStack.pop();
        }

        if (helperStack.empty()) {
            result[i] = -1;
        } else {
            // The top of stack is the next greater element
            result[i] = helperStack.top();
        }

        helperStack.push(currentVal);
    }

    return result;
}


} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
