#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const{
    Stack<T> temp= this ->stack;
    vector<T> v;
    while(!temp.isEmpty()){
        v.push_back(temp.top());
        temp.pop();
    }
    int left =0;
    int right =v.size()- 1;
    while(left<right){
        if(v[left]!=v[right])
            return false;
            left++;
            right--;
    }
    return true;
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
    Stack<T> temp;
    unordred_set<T> ;
    while(!=stack.isEmpty()){
        T val = stack.top();
        stack.pop();
    }
    Stack<T> finalStack;
    while(!temp.isEmpty()){
        finalStack.push(temp.top());
        temp.pop();
    }
    stack=finalStack;
}
#endif // STACK_QUESTIONS_MEMBER_TPP
