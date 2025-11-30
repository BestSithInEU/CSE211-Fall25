#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"
using namespace std;

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implement this function
  while(!source.isEmpty()){
        int x = source.pop();
        if(x%2==0){
            stack2.push(x);
        }else{
            stack1.push(x);
        }




  }

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
