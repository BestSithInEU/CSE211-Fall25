#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  if(stack.isEmpty()){
  return 0;
}
if (stack.size()==1){
return 1;   // Stack (top to bottom): 8, 7, 6, 5, 3, 2, 1
}
Stack<T> temp; 
while (!stack.isEmpty()){
	temp.push(stack.top());  // temp top to bottom: 1 2 3 5 6 7 8 
	stack.pop();
}
	T count=1;
	T first= temp.top();  // 1
	temp.pop();  	//temp 2 3 5 6 7 8
	stack.push(first);	//stack: 1	
while(!temp.isEmpty()){
	T cur=temp.top();   
	temp.pop();
	stack.push(cur);
	if( cur== first+1 || cur== first-1){
		count= count+1;
	}
	first=current;
	
}
return count;
}


// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
 
if(k>0){
	T temp1; 
  T temp2;
  for(int i=0; i<k;i++){
 	 temp1.push(stack.top());    // Original: Stack (top to bottom):5, 4, 3, 2, 1 // temp1: 4 5
 	 stack.pop();   // stack: 3 2 1 
 }
 while(!stack.isEmpty()){
 	temp2.push(stack.top()); //temp2 :1 2 3
 	stack.pop();  
}
while(!temp1.isEmpty){
	stack.push(temp1.pop()); //stack 5 4
	temp1.pop();
}
 while(!temp2.isEmpty()){
 	stack.push(temp2.pop());  //stack: 3 2 1 5 4 
 	temp2.pop();
}
return stack;
}
if(k<0){
	k=k*-1;
	T rotatedStack;
	T temp1;
	T temp2;
	T temp2rotated;
	T temp1rotated;
	while(!stack.isEmpty()){
		rotatedStack.push(stack.top()); //rotated: 1 2 3 4 5
		stack.pop();
	}
	for(int=0;i<k;i++){
		temp1.push(rotatedStack.top()); //temp1: 2 1
		rotatedStack.pop();  //rotatedStack : 3 4 5
} 
	while(!rotatedStack.isEmpty()){
		temp2.push(rotatedStack.top()); //temp2; 5 4 3 
		rotatedStack.pop(); 
}

	while(!temp2.isEmpty()){ 
		temp2rotated.push(temp2.top()); //temp2rotated: 3 4 5
		temp2.pop();
}
		
	while(!temp2rotated.isEmpty()){
		stack.push(temp2rotated.top()); //stack: 5 4 3
		temp2rotated.pop();
}

	while(!temp1.isEmpty()){ 
		temp1rotated.push(temp1.top()); //temp1rotated: 1 2
		temp1.pop();
}
	while(!temp1rotated.isEmpty()){
		stack.push(temp1rotated.top()); // stack: 2 1 5 4 3
		temp1rotated.pop();
}
		
		return stack;



} 
  
}
 
  
  
  
  
  
  
}

#endif // STACK_QUESTIONS_MEMBER_TPP
