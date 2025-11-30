#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP
#include <stack> // i need use theese
#include <string>
#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // TODO: IMPLEMENTATION
// the variables i use. two temporary stacks.
stack<int>tempstack;
stack<int>tempmainstack;
stack<int>tempstack = potential;
stack<int>tempmainstack = mainStack;
int size = mainStack.size();

//main loop part
    for(int i = 0;i<=size;i++){
    if(tempmainstack.top() = tempstack.top){
        tempstack.pop();
        tempmainstack.pop;
        }
        else{
        tempmainstack.pop
        }
}
// end of main loop. checking the temp stack to find answer.
    if(!tempmainstack.isempty){
        return false;
    }
    else{
        return true;
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
