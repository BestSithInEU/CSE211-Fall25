#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
}
Stack<T> s=top();
Stack <T> temp=*this;
size_t
int n=s.size();
if(s.top()==nullptr){
    cout<<"underflow_error";
}
while(!s.isEmpty()){
    for(int i=0;i<(this->size)/2;i++){
            if(n%2==0){
                return this->data;
            }
            if(n%2!=0){
                return this->data;

            }
    getKthFromTop();
    }
//Node <T>*slow=s.top();
//Node <T>*fast=nullptr;
//while(!s.isEmpty()){
//      if(i=0;i<n;i++){
//         slow=slow->next;
//         fast=fast->next->next;
//      }
//      if(slow==fast){
//         return n/2;
//      }
//getKthFromTop();
//}
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {

  // TODO: Implement this function
}
Stack<T> s;
Stack<T> temp=*this;
while(!s.isEmpty()){
    temp.push(s.top());
    s.pop();
}
while(!temp.isEmpty()){
    cout<<temp.top();
    temp.pop();

}

#endif // STACK_QUESTIONS_MEMBER_TPP
