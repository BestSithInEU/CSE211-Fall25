#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {

    Stack<T> m = mainStack;
    Stack<T> p = potential;

    if (p.isEmpty()) {
        return true;
    }

    while (!m.isEmpty()) {
        if (!p.isEmpty() && m.top() == p.top()) {
            p.pop();
        }
        m.pop();
    }
    return p.isEmpty();
}



#endif // STACK_QUESTIONS_NON_MEMBER_TPP
