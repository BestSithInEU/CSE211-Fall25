#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"
#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack) {
	
	size_t mySize = stack.size();
	
	if(mySize <= 1) return ;
	Stack<T> myTemp = stack;
	std::vector<T> myValues2 ;
	
	myValues2.reserve(mySize);
	
	while(!myTemp.isEmpty()){
		myValues2.push_back(myTemp.top());
		myTemp.pop();
		
	}
	
std:: reverse(myValues2.begin(),myValues2.end());

size_t bCount = mySize/2 + (mySize %2);
size_t tCount = mySize/2;

std::vector<T> interL;
interL.reserve(mySize);

for(size_t m = 0; m< tCount; m++){
	interL.push_back(myValues2[m]);
	interL.push_back(myValues2[bCount + m]);
	
}
	
	
if(bCount<tCount){
	
	interL.push_back(myValues[bCount-1]);
}

Stack<T> reStack ;
for(size_t i = 0;i<interL.size();i++){
	reStack.push(interL[i]);
	
}

stack = reStack;
	
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This
}
} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
