#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP
using namespace std;
#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {

    if (this->isEmpty())
        return 0;
    Stack<T> copy = *this;
    Stack<T> temp;
    while (!copy.isEmpty()) {
        temp.push(copy.top());
        copy.pop();
    }

    size_t longest = 1;
    size_t current = 1;

    T prev = temp.top();
    temp.pop();


    while (!temp.isEmpty()) {
        T curr = temp.top();
        temp.pop();

        if (abs(curr - prev) == 1) {
            current++;
        } else {
            if (current > longest)
                longest = current;
            current = 1;
        }

        prev = curr;
    }

    if (current > longest)
        longest = current
    return longest;
}


// TODO: Implement This

// ============================================================================
// Question 2: rotateStack
// ============================================================================

  // TODO: Implement This
  template <typename T> void StackQuestions<T>::rotateStack(int k) {




    if (this->size() <= 1)
        return;

    int n = this->size();
    vector<T> arr;
    arr.reserve(n);


    while (!this->isEmpty()) {
        arr.push_back(this->top());
        this->pop();}

    reverse(arr.begin(), arr.end());
    k = k % n;
    if (k < 0)
        k += n;


    rotate(arr.begin(), arr.begin() + (n - k), arr.end());

    for (int i = 0; i < n; i++)
        this->push(arr[i]);
}


#endif // STACK_QUESTIONS_MEMBER_TPP
