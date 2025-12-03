#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T>
void interleaveHalves(Stack<T>& stack) {
    Stack<T> tempSt;
    int len = 0;
    while (!stack.isEmpty()) {
        tempSt.push(stack.top());
        stack.pop();
        len++;
    }

    int halfLen = (len + 1) / 2;

    Stack<T> topHalf;
    Stack<T> botHalf;
    while (halfLen--) {
        topHalf.push(tempSt.top());
        tempSt.pop();
    }

    while (!tempSt.isEmpty()) {
        botHalf.push(tempSt.top());
        tempSt.pop();
    }

    while (!botHalf.isEmpty() || !topHalf.isEmpty()) {
        if (!botHalf.isEmpty()) {
            stack.push(botHalf.top());
            botHalf.pop();
        }
        if (!topHalf.isEmpty()) {
            stack.push(topHalf.top());
            topHalf.pop();
        }
    }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T>
std::vector<T> nextGreaterElement(Stack<T> stack) {
    std::vector<T> nums;

    while (!stack.isEmpty()) {
        nums.push_back(stack.top());
        stack.pop();
    }

    std::reverse(nums.begin(), nums.end());

    int n = nums.size();
    std::vector<T> result(n, -1);
    Stack<T> monoSt;


    for (int i = n - 1; i >= 0; --i) {
        while (!monoSt.isEmpty() && monoSt.top() <= nums[i]) {
            monoSt.pop();
        }
        if (!monoSt.isEmpty()) {
            result[i] = monoSt.top();
        }
        monoSt.push(nums[i]);
    }

    return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
