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
    Node* main = mainStack.topNode;

    for(int i = 0; i<mainStack.size();i++){
        Node* sub = potential.topNode;
        int count = 0;
        while(main -> data == sub -> data){
            count++;
            if(count == potential.size())return true;
        main = main -> next;
        sub =  sub -> next;
        }
    }
    main = main -> next;
}
return false;

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
