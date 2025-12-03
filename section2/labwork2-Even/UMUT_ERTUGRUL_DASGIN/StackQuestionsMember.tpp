#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
    StackQuestions<T> tempSt = *this;

    if (tempSt.isEmpty()) return 0;

    int maxC = 1;
    int tempMaxC = 1;

    int topVal = tempSt.top();
    tempSt.pop();

    while (!tempSt.isEmpty()) {
        if (tempSt.top() == topVal - 1) {
            topVal = tempSt.top();
            tempMaxC++;
            tempSt.pop();
        } else {
            if (tempMaxC > maxC) maxC = tempMaxC;
            tempMaxC = 1;
            topVal = tempSt.top();
            tempSt.pop();
        }
    }

    if (tempMaxC > maxC) maxC = tempMaxC;

    return maxC;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T>
void StackQuestions<T>::rotateStack(int k) {
    int len = this->size();
    if (len == 0) return;

    k = k % len;
    if (k < 0) k = len + k;
    if (k == 0) return;

    std::vector<T> nums;
    while (!this -> isEmpty()) {
        nums.push_back(this -> top());
        this -> pop();
    }

    std::vector<T> finalArr(len);
    for (int i = 0; i < len; ++i) {
        int idx = i - k;
        if (idx < 0) idx += len;
        finalArr[idx] = nums[i];
    }

    for (int i = len - 1; i >= 0; --i) {
        this -> push(finalArr[i]);
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
