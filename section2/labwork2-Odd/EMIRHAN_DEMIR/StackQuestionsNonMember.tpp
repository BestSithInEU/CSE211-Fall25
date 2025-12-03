#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T>& stack1, Stack<T>& tack2) {
    Stack<T> s1 = stack1;
    Stack<T> s2 = stack2;

    std::vector<T> v1, v2;

    while (!s1.isEmpty()) {
        v1.push_back(s1.top());
        s1.pop();
    }

    while (!s2.isEmpty()) {
        v2.push_back(s2.top());
        s2.pop();
    }

    std::vector<T> merged;
    int i = 0, j = 0;

    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j]) {
            merged.push_back(v1[i]);
            i++;
        } else {
            merged.push_back(v2[j]);
            j++;
        }
    }

    while (i < v1.size()) {
        merged.push_back(v1[i]);
        i++;
    }
    while (j < v2.size()) {
        merged.push_back(v2[j]);
        j++;
    }

    Stack<T> result;
    for (int k = merged.size() - 1; k >= 0; k--) {
        result.push(merged[k]);
    }

    return result;
 
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
