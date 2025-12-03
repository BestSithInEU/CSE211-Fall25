#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
#include <vector>
template <typename T> void interleaveHalves(Stack<T> &stack){
int sizeStack=stack.size();
if(sizeStack<=1){
return 1;
}
std::vector<T> v;
v.reserve(sizeStack());

while(!stack.isEmpty){
	v.push_back(stack.top());
	stack.pop();

}
std::reserve(v.begin());
std::reserve(v.end());
 


}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
}

} // namespace StackUtils




















   k
   
   
   
