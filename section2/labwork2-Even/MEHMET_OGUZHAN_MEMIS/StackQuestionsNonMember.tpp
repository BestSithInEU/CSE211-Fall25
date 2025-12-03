#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack <T>& stack){
    std::vector<int> top;
    std::vector<int> bottom;
    std::vector<int> temp;

    while(!stack.isEmpty()){
        temp.push_back(stack.top());
        stack.pop();
    }
    if (temp.size() % 2 == 0){
        for (int i = temp.size() - 1; i <= temp.size() / 2; i--){
            bottom.push_back(temp[i]);
        }
        for (int j = temp.size() - 1; j <= 0; j--){
            top.push_back(temp[j]);
        }
    }else{
        for (int k = temp.size() - 1; k <= (temp.size() + 1) / 2; k--){
            bottom.push_back(temp[k]);
        }
        for (int l = temp.size() - 1; l <= 0; l--){
            top.push_back(temp[l]);
        }
    }

    for(int m = 0; m < top.size(); m++){
        std::cout << bottom[m] + top[m];
    }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
