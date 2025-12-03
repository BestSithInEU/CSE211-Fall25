#ifndef STACK_QUESTIONS_NON_MEMBER_H
#define STACK_QUESTIONS_NON_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T> void interLeaveHalves(Stack<T> &stack){
	
}
namespace StackUtils {
// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
/**
 * @brief Interleave bottom half and top half of stack
 * @param stack The stack to interleave (modified in place)
 *
 * Time: O(n), Space: O(n)
 * Approach: Split into two halves and merge alternately
 *
 * Example: [1,2,3,4,5,6] (top=1) -> [1,4,2,5,3,6] (top=1)
 *          Bottom half: [6,5,4], Top half: [3,2,1]
 *          Interleaved: [4,1,5,2,6,3] reversed -> [3,6,2,5,1,4]
 */
template <typename T> void interleaveHalves(Stack<T> &stack);

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
/**
 * @brief Find next greater element for each element in stack
 * @param stack Input stack
 * @return Vector where result[i] = next greater element or -1
 *
 * Time: O(n), Space: O(n)
 * Approach: Monotonic decreasing stack
 *
 * Example: [4,5,2,10] -> [5,10,10,-1]
 */
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack){
	
	int n = stack.size();
    vector<T> result(n, T(-1));

    vector<T> arr;
    arr.reserve(n);

    while (!stack.empty()) {
        arr.push_back(stack.top());
        stack.pop();
    }

    Stack<T> mono;

    for (int i = 0; i < n; i++) {
        while (!mono.empty() && arr[i] > arr[mono.top()]) {
            int idx = mono.top();
            mono.pop();
            result[idx] = arr[i];
        }
        mono.push(i);
    }

    return result;
}
} // namespace StackUtils

// Include template implementation
#include "StackQuestionsNonMember.tpp"

#endif // STACK_QUESTIONS_NON_MEMBER_H
