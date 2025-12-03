#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  size_t stackSize = this->size();
  if(this->size() == 0 || this->size() == 1)
    return stackSize;

  Stack<T> tempStack(*this)
  size_t longestSequence = 0;
  size_t currentSequence = 0;
  bool decreasing = false;
  T lastElement = tempStack.top();

  for(size_t i = 0; i < stackSize; i++)
  {
    tempStack.pop();
    T currentElement = tempStack.top();
    if(lastElement -1 == currentElement)
    {
        if(decreasing)
            currentSequence++;
        else
        {
            if(currentSequence > longestSequence)
                currentSequence = longestSequence;

            currentSequence = 1;
            decreasing = true;
        }
    }
    else if(lastElement +1 == currentElement)
    {
        if(!decreasing)
            currentSequence++;
        else
        {
            if(currentSequence > longestSequence)
                currentSequence = longestSequence;

            currentSequence = 1;
            decreasing false;
        }
    }
    if(currentSequence > longestSequence)
        currentSequence = longestSequence;
    return longestSequence;
  }
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
    size_t stackSize = this->size();
    if(this->size() == 0 || this->size() == 1)
        return;

    k = k % static_cast<int> stackSize;

    if(k == 0)
        return;

    Stack<T> tempStack;
    Stack<T> tempStack2

    if(k > 0)
    {
        for(int i = 0; i < k; i++)
        {
            tempStack.push(this->top());
            this->pop();
        }
    }
    else if(k < 0)
    {
        for(int i = 0; i < (stackSize + k); i++)
        {
            tempStack.push(this->top());
            this->pop();
        }
    }
    while(!this->isEmpty())
    {
        tempStack2.push(this->top());
        this->pop();
    }
    while(!tempStack.isEmpty())
    {
        this->push(tempStack.top());
        tempStack.pop();
    }
    while(!tempStack2.isEmpty())
    {
        this->push(tempStack2.top());
        tempStack2.pop();
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
