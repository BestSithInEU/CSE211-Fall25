#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template<typename T> void interLeaveHalves(Stack<T> stack){
  // TODO: Implement This
  if(stack.empty())return 0;
  if(stack.size() == 1)return;
  int n = stack.size();
  stack<T> *sp = &stack;
  std::vector<T> toptobottom;
  while(!sp->empty()){
        T ind = sp->top();
        toptobottom.push(ind);
        sp->pop();
}
std::vector<T> bottomtotop(n);
for(int i= 0; i<n;i++){
    bottomtotop[i] = toptobottom[n - 1 - i ];

}



// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
