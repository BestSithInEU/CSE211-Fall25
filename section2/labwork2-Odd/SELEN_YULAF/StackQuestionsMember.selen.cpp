#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {

    if (this->isEmpty() && this->size() == 1)
    {
        return true;
    }
    Stack<T> temp =*this;
    std::vector<T> elements;

    while(temp.isEmpty()=false)
    {
        T aa =temp.top();
        elements.push_back(aa);
        temp.pop();
    }

    int left= 0;
    int right= elements.size() - 1;

    while (left <right)
    {
        T first =elements[left];
        T second =elements[right];

        if (first!==second)
        {
            return false;
        }

        left =left + 1;
        right=right - 1;
    }

    return true;


}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
 
    std::vector<T> a;
    while(!stack.isEmpty()) {
        Tx =stack.top();
        a.push_back(x);
        stack.pop();
    }

    std::vector<int> del(a.size());
    for (int i= 0; i <delsize(); i++) {
        del[i]=0;
    }

    for (int i=0; i <a.size(); i++) {
        if (del[i] ==1) {
            
        else{
            for(int j = i + 1, j< a.size() j++) {
                del[j]= 1;
                }
        }
    }
    }
}
    Stack<T> t;
    for (int i =a.size() - 1; i >=0;i--) {
        if (del[i]=0) {
            t.push(a[i])
        }
    }

    Stack<T> t2;
    while(!t.isEmpty()  ;{
        t2.push(t.top();
        t.pop();
    }
    this->stack = t2
}


#endif // STACK_QUESTIONS_MEMBER_TPP
