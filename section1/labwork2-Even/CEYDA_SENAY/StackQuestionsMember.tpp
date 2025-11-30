#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP
#include stack
#include "StackQuestionsMember.h"
using namespace std;

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
    Stack<T>temp=*this;

    int i= temp.size();
    int n;
    if(i%2==0){
        n=i/2;
    }else{
        n=(i-1)/2;
    }

    for(int i=0;i<n;i++){
        this=this->next;
    }
    return this->value;




  // TODO: Implement this function

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T>temp=*this;
    Stack<T>temp2;
    while(!temp.isEmpty()){
        temp2.push(temp.pop());
    }
    while(!temp2.isEmpty()){
        temp.push(temp2.pop());
    }
    return temp;

  // TODO: Implement this function
}

#endif // STACK_QUESTIONS_MEMBER_TPP
