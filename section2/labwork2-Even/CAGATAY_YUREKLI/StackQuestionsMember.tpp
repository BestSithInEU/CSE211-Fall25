#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
	if(this->isEmpty())
	{
		return -1;
	}
	else if(this->size() == 1)
	{
		return 1;
	}
	else{
		Stack<T> temp = *this;
		int currentCounter = 1;//for counting the current suquence will be reset if difference is not 1 anymore
		int max = 1; // for recording max sequence
		
		T prevVal = tempStack.top();
    	tempStack.pop();

    	while (!tempStack.isEmpty()) {
        	T currentVal = tempStack.top();
        	tempStack.pop();


	        if (currentVal - prevVal == 1 || currentVal - prevVal == -1) 
			{
	            currentCounter++;
	        } 
			else 
			{
	            if (currentCounter > max) {
	                max = currentCounter;
	            }
	            currentCounter = 1; 
	        }
	        
	        prevVal = currentVal;
	    }

	    if (currentCounter > max) {
	        max = currentCounter;
	    }
	
	    return max;
	}		
}
	



// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
	if(this->isEmpty() || (k == 0)
	{
		return;
	}
	
	int n;
	int leftShift;
	if(k > 0)
	{
		n = k % (this->size());
		leftShift = (this->size()) - n;
	}
	else
	{
		leftShift = (-1 * k) % (this->size());
	}
	
	//leftshift kadar pop edicem 1.stacke sonra kalanlari 2.stacke pop edicem sonra ana stacke geri aticam
	Stack<T> temp1;
	Stack<T> temp2;
	
	int counter = 0;
	while(!this->isEmpty())
	{
		if(counter < leftShift)
		{
			temp1.push(this->top());
			this->pop();
			counter++;
		}
		else{
			temp2.push(this->top());
			this->pop();
		}	
	}
	
	while(!temp1.isEmpty())
	{
		this->push(temp1.top());
		temp1.pop();
	}
	
	while(!temp2.isEmpty())
	{
		this->push(temp2.top());
		temp2.pop();
	}  
}

#endif // STACK_QUESTIONS_MEMBER_TPP
