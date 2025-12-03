#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {

  // TODO: Implement This
    stack<T> stack1;
    stack<T> temp;
    stack<T> stack2;
    if(stack1.size() == 0){
        return 0;
    }
    if(stack1.size() == 1){
        return 1;
    }
    while(stack1.size() != 0){
        size_t element = stack1.top();
        stack1.pop();
        if(stack1.top()==element + 1 || stack1.top()==element - 1){
            temp.push(element);
            temp.push(stack1.pop());
        }
        stack2.push(stack1.pop());
    }
    for(size_t i =0;i<)
    if(temp.size()>stack2.size()){
        for(size_t i =0;i<temp.size();i++){
            return temp.top();
            temp.pop()
        }
    }
    else if(temp.size()<stack2.size()){
        for(size_t i =0;i<stack2.size();i++){
            return stack2.top();
            stack2.pop()
        }
    }


}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
    stack<T> stack1;
    stack<T> last;
    if(stack1.size() == 0){
        return;
    }
    for(size_t i=0;i<stack1.size()-k-1;i++){
        last.push(stack1.top());
        stack1.pop();
    }
    stack<T> reversed;
    while(stack1.size()!=0){
        reversed.push(stack1.top());
        stack1.pop();
    }
    while(reversed.size()!=0){
        last.push(reversed.top());
        reversed.pop();
    }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
