#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {
// Question 3: Interleave Halves
// ============================================================================
// TODO: Implement This
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack){
    stack<T> topHalf;
    size_t mid = stack.size()/2 - 1;
    if(stack.size() == 0){
        return;
    }
    for(size_t i=0;i<mid;i++){
        topHalf.push(stack.top());
        stack.pop();
    }
    stack<T> last;
    while(topHalf.size()!=0|| stack.size() != 0){
        if(topHalf.size() == 0){
            last.push(stack.pop());
        }
        else if(stack.size() == 0){
            last.push(topHalf.pop());
        }
        last.push(stack.pop());
        last.push(topHalf.pop());
    }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
    std::vector<T> vec;
    vec.size() = stack.size();
    while(stack.size()!=0){
        vec.push(stack.pop());
    }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
