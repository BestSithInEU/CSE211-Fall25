#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
bool StackQuestions::getKthFromTop(size_t & k) const {

   if (isEmpty())
      return false;
   else {
      stackTop = topPtr->item;
      return true;
   }

}

}



// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
void StackQuestions::sortStack(const Stack& aStack){

   if (aStack.topPtr == NULL)
      topPtr = NULL;

   else {
      topPtr = new StackNode;
      topPtr->item = aStack.topPtr->item;

      StackNode *newPtr = topPtr;
      for (StackNode *origPtr = aStack.topPtr->next;
                      origPtr != NULL;
                      origPtr = origPtr->next){
         newPtr->next = new StackNode;
         newPtr = newPtr->next;
         newPtr->item = origPtr->item;
      }
      newPtr->next = NULL;
   }
}


}

#endif // STACK_QUESTIONS_MEMBER_TPP
