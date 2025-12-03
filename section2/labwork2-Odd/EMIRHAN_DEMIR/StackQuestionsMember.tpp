#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  
    if (this->stack.isEmpty() || this->stack.size() == 1)
        return true;

    
    Stack<T> temp = this->stack;

    
    std::vector<T> vector;
    while (!temp.isEmpty()) {
        vector.push_back(temp.top());
        temp.pop();
    }

    
    int left = 0;
    int right = vector.size() - 1;

    while (left < right) {
        if (vector[left] != vector[right])
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

  if (this->stack.isEmpty()) return;

    std::set<T> temp;     
    Stack<T> temp2;        

    
    while (!this->stack.isEmpty()) {
        T value = this->stack.top();
        this->stack.pop();

        
        if (temp.count(value) == 0) {
            temp.insert(value);
            temp2.push(value);
        }
        
    }

    while (!temp2.isEmpty()) {
        this->stack.push(temp2.top());
        temp2.pop();
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
