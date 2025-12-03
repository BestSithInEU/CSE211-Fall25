#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
      if (this->isEmpty())
        return 0;

    Stack<T> tmp = *this;
    std::vector<T> v;
    while (!tmp.isEmpty()) {
        v.push_back(tmp.top());
        tmp.pop();
    }
    if (v.size() == 1)
        return 1;


    size_t maxLen = 1;
    size_t curr = 1;



    for (size_t i = 1; i < v.size(); i++) {
        if (std::abs(v[i] - v[i - 1]) == 1) {
            curr++;
        } else {
            if (curr > maxLen)
                maxLen = curr;
            curr = 1;
        }
    }
    if (curr > maxLen)
        maxLen = curr;
    return maxLen;
}


// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  if (this->isEmpty() || this->size() < 2)
        return;

    int n = this->size();
    k = k % n;
    if (k < 0)
        k = n + k;
    if (k == 0)
        return;

    Stack<T> tmp = *this;
    std::vector<T> v;

    while (!tmp.isEmpty()) {
        v.push_back(tmp.top());  
        tmp.pop();
    }

    std::vector<T> rotated(n);
    for (int i = 0; i < n; i++) {
        rotated[(i + k) % n] = v[i];
    }
    while (!this->isEmpty())
        this->pop();
    for (int i = 0; i < n; i++) {
        this->push(rotated[i]);
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
