#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

using namespace std;
#include<stack>

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
	
	Stack<T> s = stack;

    if (s.isEmpty()) return 0;
    if (s.size() == 1) return 1;

    size_t curr = 1;
    size_t best = 1;

    while (s.size() >= 2) {
        T x = s.pop();      
        T y = s.pop();   	

        if (x - y == 1 || x - y == -1) {
            curr++;
        } 
		else
		{
            curr = 1;
        }

        if (curr > best)
            best = curr;

        s.push(y);
    }

    return best; 
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
 
    Stack<T> s = stack;
    int n = s.size();
    if (n <= 1 || k == 0) {
        stack = s;
        return;
    }

    k = k % n;
    if (k < 0) k = n + k;  

    Stack<T> temp1;
    Stack<T> temp2;

    for (int i = 0; i < k; i++) {
        temp1.push(s.pop());
    }

    while (!s.isEmpty()) {
        temp2.push(s.pop());
    }

    Stack<T> result;
    while (!temp2.isEmpty()) {
        result.push(temp2.pop());
    }

    Stack<T> reverseTemp;
    while (!temp1.isEmpty()) {
        reverseTemp.push(temp1.pop());
    }
    while (!reverseTemp.isEmpty()) {
        result.push(reverseTemp.pop());
    }

    stack = result;
}

#endif // STACK_QUESTIONS_MEMBER_TPP
