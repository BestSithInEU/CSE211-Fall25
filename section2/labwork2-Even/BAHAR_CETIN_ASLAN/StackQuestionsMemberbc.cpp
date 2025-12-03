#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"
#include <vector>
// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
if (isEmpty)
{ 
return 0;
}
if (stackSize==)
{
return 1;
}
StackQuestions <T> tempStack = *this;

std::vector<T> elements;

while (!tempsStack.isEmpty){
vektor.push_back(tempStack.top());
tempStack.pop();
}
size_t max=1;
size_t sequence=1;

for (i=0; i<elements.size()-1; i++)
{
   T value1= elements [i];
   T value2= elements [elements.size()+1];
   if ((value1-value2==1) || (value2-value1==1))
   { 
     sequence++;
   }
   if (sequence>max){
   max=sequence;
   }
   return max;
 }
   
  
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
 
 if(is.Empty)
 { 
 return 0;
 }
 if (stackSize == 1)
 {
 return 0;
 }
 int n = stackSize;
 Stack<T> stack1;
 Stack<T> stack2;
 Stack<T> stack3;
 Stack<T> stack4;
 Stack<T> resultStack1;
 Stack<T> resultStack2;
 if (k/n >0 )
 {
   for (i=0; i<=k; i++){
   stack1.push(this.top());
   this->pop()
   }
   for (i=k+1; i<=stackSize -1; i++){
   stack2.push(this.top());
   this-> pop();
   }
   resultStack1 = stack1;
   resultStack1= stack2;
   return resultStack1;
   
 }
 else if (k/n<0)
 {
   for(i=0; i<=stackSize-k; i++){
   stack3.push(this.top);
   this->pop();
   }
   for (i=k+1; i<=stackSize -1; i++){
   stack4.push(this.top());
   this-> pop();
   }
   resultStack2 = stack3;
   resultStack= stack4;
   return resultStack1;
 }
   
   
 
}

#endif // STACK_QUESTIONS_MEMBER_TPP
