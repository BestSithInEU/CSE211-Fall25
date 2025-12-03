#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack) {
    size_t stackSize = stack.size();
    if(stackSize == 0 || stackSize == 1)
        return;

    int topSize = static_cast<int>(stackSize) / 2;
    int bottomSize = static_cast<int>(stackSize) - topSize;

    Stack<T> topHalf;
    Stack<T> bottomHalf;
    Stack<T> topHalfReverse;
    Stack<T> bottomHalfReverse;

    for(int i = 0; i < topSize; i++)
    {
        topHalf.push(stack.top());
        stack.pop();
    }
    for(int i = 0; i < bottomHalf; i++)
    {
        bottomHalf.push(stack.top());
        stack.pop()
    }
    while(!topHalf.isEmpty())
    {
        topHalfReverse.push(topHalf.top());
        topHalf.pop();
    }
    while(!bottomHalf.isEmpty())
    {
        bottomHalfReverse.push(bottomHalf.top());
        bottomHalf.pop();
    }
    while(!bottomHalfReverse.isEmpty() && !topHalfReverse.isEmpty())
    {
        stack.push(topHalfReverse.top());
        topHalfReverse.pop();
        stack.push(bottomHalfReverse.top());
        bottomHalfReverse.pop();
    }
    while(!bottomHalfReverse.isEmpty())
    {
        stack.push(bottomHalfReverse.top());
        bottomHalfReverse.pop();
    }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
    stack<T> monotonicDecreasingStack;
    std::vector<T> result;
    std::stack<T> tempStack;

    while (!stack.isEmpty())
    {
        tempStack.push(stack.top());
        stack.pop();
    }

    while (!tempStack.isEmpty())
    {
        T current = tempStack.top();
        tempStack.pop();

        while (!monotonicDecreasingStack.isEmpty() && monotonicDecreasingStack.top() <= current)
            monotonicDecreasingStack.pop();

        if (monotonicDecreasingStack.isEmpty())
            result.push_back(-1);
        else
            result.push_back(monotonicDecreasingStack.top());

        monotonicDecreasingStack.push(current);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
