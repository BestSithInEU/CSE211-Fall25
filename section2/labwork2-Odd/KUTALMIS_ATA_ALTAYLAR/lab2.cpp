#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
std::stack<T> tempstk = this->stack_; 
    std::queue<T> tempqx; 

    std::stack<T> axystk = this->stack_; 
    while (!axy.empty()) {
        tempqx.push(axystk.top());
        axystk.pop();
    }
    
    while (!tempstk.empty()) {
        if (tempstk.top() != tempqx.front()) {
            return false; 
        }
        tempstk.pop();
        tempqx.pop();
    }

    return true; 
}

  // TODO: Implementation
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
std::unordered_set<T> seenElements; 
    Stack<T> tempstk; 

    while (!this->stack_.isEmpty()) {
        T current = this->stack_.top();
        this->stack_.pop();

        if (seenElements.find(current) == seenElements.end()) {
            seenElements.insert(current);
            tempstk.push(current); 
        }
    }

    while (!tempstk.isEmpty()) {
        this->stack_.push(tempStack.top());
        tempstk.pop();
    }


  // TODO: Implementation
}

#endif // STACK_QUESTIONS_MEMBER_TPP


