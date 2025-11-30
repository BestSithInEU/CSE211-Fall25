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

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
/**
 * @brief Split stack into two by alternating elements
 * @param source Source stack (will be emptied)
 * @param stack1 First output stack
 * @param stack2 Second output stack
 *
 * Time: O(n), Space: O(1)
 * Approach: Pop and alternate between two stacks
 *
 * Example: [1,2,3,4,5] (top=1) -> stack1=[1,3,5], stack2=[2,4]
 */
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2);

// ============================================================================
// Question 4: Simplify Unix Path
// ============================================================================
/**
 * @brief Simplify a Unix file path
 * @param path Unix path (e.g., "/a/./b/../../c/")
 * @return Simplified path (e.g., "/c")
 *
 * Time: O(n), Space: O(n)
 * Approach: Stack-based directory navigation
 *
 * Handles: ., .., //, multiple slashes
 */
std::string simplifyPath(const std::string &path);
} // namespace StackUtils

// Include template implementation
#include "StackQuestionsNonMember.tpp"

#endif // STACK_QUESTIONS_NON_MEMBER_H
