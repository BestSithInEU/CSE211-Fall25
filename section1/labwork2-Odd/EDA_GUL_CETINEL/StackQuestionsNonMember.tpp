#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
    Stack<T> temp = mainStack;
    Stack<T> pot = potential;
    T topOfPotential = pot.top();
    T topOfTemp;
    while (!temp.isEmpty())
    {
        topOfTemp = temp.top();
        if(topOfTemp == topOfPotential)
        {
            pot.pop();
            if(pot.isEmpty())
            {
                return true;
            }
            topOfPotential=pot.top();
        }
        temp.pop();
    }
    return false;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
