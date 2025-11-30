#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implement this function
  while(!source.isEmpty()){
    int top = source.top();
    source.pop();
    stack1.push(top);
    int top2 = source.top();
    source.pop();
    stack2.push(top2);
  }

  Stack<T> temp1 = *this;
  Stack<T> temp2 = *this;

  while(!stack1.isEmpty()){
    int top = int(stack1.top());
    stack1.pop();
    temp1.push(top);
  }

  while(!temp1.isEmpty()){
    int top = temp1.top();
    temp1.pop();
    temp2.push(top);
  }

  while(!temp2.isEmpty()){
    int top = temp2.top();
    temp2.pop();
    stack1.push(top);

  }

  while(!stack2.isEmpty()){
    int top = int(stack2.top());
    stack2.pop();
    temp1.push(top);
  }

  while(!temp1.isEmpty()){
    int top = temp1.top();
    temp1.pop();
    temp2.push(top);
  }

  while(!temp2.isEmpty()){
    int top = temp2.top();
    temp2.pop();
    stack2.push();

  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
