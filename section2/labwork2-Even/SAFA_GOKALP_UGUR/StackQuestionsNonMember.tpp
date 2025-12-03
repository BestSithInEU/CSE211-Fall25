#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"
#include <stack>
using namespace std;
namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack){
	
	int x = stack.size();
    if (x <= 1)
        return;

	Stack<T> reverse;      
    Stack<T> bottom;  
    Stack<T> top;      
    Stack<T> result; 
	 
	Stack<T> temp = stack;
    while (temp.empty() !=1) {
        reverse.push(temp.top());
        temp.pop();
    }
    //1 2 3 4 5 6
    //1 2 3 4 5 6 7
	int mid = x / 2;  
    int bottomCount = x - mid;
    int topCount = mid;
	
	for (int i = 0; i < bottomCount; i++) {
        bottom.push(rev.top());
        reverse.pop();
    }
    for (int j = 0; j < topCount; j++) {
        top.push(rev.top());
        reverse.pop();
    }
    
    Stack<T> bTemp = bottom;
    Stack<T> tTemp = top;

    while (bTemp.empty() !=1 || tTemp.empty()!=1) {
        if (bTemp.empty() !=1) {
            result.push(bTemp.top());
            bTemp.pop();
        }
        if (tTemp.empty() !=1) {
            result.push(tTemp.top());
            tTemp.pop();
        }
    }

    stack.clear();
    while (result.empty() !=1) {
        stack.push(result.top());
        result.pop();
    
    
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> vector<T> nextGreaterElement(Stack<T> stack) {
  
  Stack<T> order;
    while (!stack.empty()) {
        order.push(stack.top());   // order.top() = bottom
        stack.pop();
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP

