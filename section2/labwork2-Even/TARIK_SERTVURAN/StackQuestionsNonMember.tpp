#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
// TODO: Implement This
template <typename T> void interleaveHalves(Stack<T> &stack) {


    std::vector<T> vec;

    Stack<T> temp = stack;





}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {



    //if(stack.isEmpty()){
      //  return 0 ;
    //}

    std::vector<T> vec;


    while(!stack.isEmpty()){
        T value = stack.top();
        stack.pop();
        vec.push_back(value);

    }

    std::reverse(vec.begin(),vec.end());

    int n = vec.size();

    std::vector<T> result(n,-1);

    for(int i = 0 ; i<n ;i++){

        for(int j = i+1; j<n; j++){
            if(vec[j]>vec[i]){
                result[i] = vec[j];
                break;
            }
        }
    }

    return result;
  // TODO: Implement This
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
