#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
// TODO: Implement This


template <typename T> void interleaveHalves(Stack<T> &stack){

    Stack<T> bottomHalf;
    Stack<T> topHalf;
    int mid = stack.size()/2;
    int i = 0;
    while(i<mid){
        topHalf.push(stack.top());
        stack.pop();
        i++;
    }
    while(!stack.isEmpty()){
        bottomHalf.push(stack.top());
        stack.pop();
    }

    while(!topHalf.isEmpty() )
    {
        stack.push(bottomHalf.top());
        stack.push(topHalf.top());
        bottomHalf.pop();
        topHalf.pop();
    }
    while(!bottomHalf.isEmpty()){
        stack.push(bottomHalf.top());
        bottomHalf.pop();
    }




}


// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This

  Stack<T> tempstack2;

  std::vector<T> result;
  int size1 = stack.size();
  int size2 = stack.size();
  int temp1;
  int temp2;
  int temp3;


  for(int i = 0;i<size1;i++){
    Stack<T> tempstack1 = Stack<T>(stack);
    while(!tempstack1.isEmpty()){
    tempstack2.push(tempstack1.top());
    tempstack1.pop();
    }
    for(int j = size1;j>size2;j--){
        tempstack2.pop();
    }
    temp1 = tempstack2.top();
    temp3 = -1;
    while(!tempstack2.isEmpty()){

        tempstack2.pop();
        temp2 = tempstack2.top();
        if(temp2 > temp1) {
            temp3 = temp2;
            break;
        }
    }
    result.push_back(temp3);
    size2--;
  }
  return result;

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
