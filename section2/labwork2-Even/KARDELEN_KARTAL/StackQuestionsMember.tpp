#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This
  
  Stack<T> stackTemp = stack; // olan stack ile oynamamak icin copyasini yaptim
  
  std::vector<T> myValues; 
  myValues.reserve(stackTemp.size());
  while(!stackTemp.isEmpty()){
  	myValues.push_back(stackTemp.top());
  	stackTemp.pop();
	    }
  
    if(stackTemp.empty()){
  	return 0; 
  	// stack bos ise return sifir
  }
  
 size_t lenghtOpt = 1;
 size_t myLength = 1;
  
   for(size_t m = 1; m<myValues.size(); ++m){
  	
  	T difference = myValues[m] - myValues[m-1];
  	
  	
  	if(difference == -1 || difference == 1){  // ardisik olanlari scanledim
  		myLength++;
  		
	  }
	else{
		
		if(myLength>lenghtOpt) {
		lenghtOpt = myLength ; myLength = 1;
	}
  	
  }
  
  if(myLength>lenghtOpt){
  	lenghtOpt =myLength;
  	return lenghtOpt;
  }
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
  
  
  
  
  
  
}



#endif // STACK_QUESTIONS_MEMBER_TPP



