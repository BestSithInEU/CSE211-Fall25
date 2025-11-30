#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // TODO: IMPLEMENTATION
  if(potential->isEmpty()) return true;
  Stack<T> s1 = *this;
  Stack<T> s2,s3 ;
  //Node* t1=mainStack->topNode;
  Node *t2=potential->topNode;

  while(t1){
    s1->push(t1->data);
    t1=t1->next;
  }
  while(t2){
    s2->push(t2->data);
    t2=t2->next;
  }
  while(!s2->isEmpty()){
    s3->push(s2->top());
    s2->pop();
  }
  //if it is a subsequence, then the reverse order does not affect the result

  while(!s1->isEmpty()){
    if(s1->top()==s3->top()){
        s3->pop();
    }
    s3->pop();
  }
  return s2->isEmpty();



}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
