#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
    StackQuestions<T>temp(*this);
    if(temp.isEmpty()== 1){
        return 0;
    }
    T previous = temp.top();
    temp.pop();

    size_t currentlength =1;
    size_t maxlength = 1;

    while(temp.isEmpty()!= 1){
        T current = temp.top();
        temp.pop();

        T check;
        if (current > previous){
            check = current / previous;
        }
        else{
            check = previous / current;
        }
        if(check == 1){
            currentlength += 1;
        }
        else{
            currentlength = 1;
        }

        if currentlength>maxlength{
            maxlength = currentlength;
        }
        previous = current
    }
    return maxlength;
}


// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
    int n = size();
    if(n<=1)return;

    k = k & n ;//artÄ±
    if(k<0){
        k = k+n;
    }
    if(k==0)return


    StackQuestions<T> temp1;
    StackQuestions<T> temp2;

    for(int i = 0; i<k-1;i++){
        temp1.push(this.top());
        this.pop();

    }
    while(this.isEmpty() != 1){
        temp2.push(this.top());
        this.pop();
    }
    while(temp2.isEmpty()!= 1){
        this.push(temp2.top);
        temp2.pop();
    }
    while(temp1.isEmpty() != 1){
        this.push(temp1.top());
        temp1.pop;
    }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
