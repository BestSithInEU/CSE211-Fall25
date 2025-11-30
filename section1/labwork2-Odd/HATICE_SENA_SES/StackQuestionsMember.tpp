#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> T StackQuestions<T>::getKthFromTop(size_t k) const {
  // TODO: IMPLEMENTATION
  void getKthFromTop() {
  
  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q1_stack");
  
  isEmpty(stack *s){ 
	return;
  }
  
  for(int k=0; exp[k]<size; size++){
  if(stack.getKthFromTop(0)){
    std::cout << "0th from top (top element): " << stack.getKthFromTop(0) << std::endl;
  }
  else if(stack.getKthFromTop(4)){
    std::cout << "4th from top (bottom element): " << stack.getKthFromTop(4) << std::endl;
  } else {
    std::cout << "[k]" << "nd from top: " << stack.getKthFromTop([k]) << std::endl;
  }
}
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
  void sortStack() {

  StackQuestions<int> stack;
  stack.loadFromJSON("examples/members.json", "q2_unsorted");

  printInfo("Original stack (top to bottom): 40, 20, 50, 10, 30");
  stack.sortStack();
  
  
  printInfo("After sorting (ascending - smallest on top):");
  stack.display();
}
}

#endif // STACK_QUESTIONS_MEMBER_TPP
