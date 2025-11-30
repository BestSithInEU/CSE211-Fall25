#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // TODO: IMPLEMENTATION
    int sum=0;
    Node* temp1=mainStack.topNode;
    Node* temp2=potential.topNode;
    int size_potential=0;
    while(temp2!=nullptr){
        size_potential++;
        temp2=temp2->next;
    }
    temp2=potential.topNode;
    while(temp1!=nullptr){
        if(temp1->item==temp2->item)
            sum++;
        temp1=temp1->next;
        temp2=temp2->next;
    }
    if(sum==size_potential)
        return true;
    return false;

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
