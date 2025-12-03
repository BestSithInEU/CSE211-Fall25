#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"
#include <vector>

template <typename T>
Stack<T> StackUtils::mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
    Stack<T> s1(stack1);
    Stack<T> s2(stack2);

    std::vector<T> v1;
    std::vector<T> v2;

    v1.reserve(s1.size());
    v2.reserve(s2.size());

    while (!s1.isEmpty()) {
        v1.push_back(s1.top());
        s1.pop();
    }

    while (!s2.isEmpty()) {
        v2.push_back(s2.top());
        s2.pop();
    }

    std::vector<T> merged;
    merged.reserve(v1.size() + v2.size());

    std::size_t i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] <= v2[j]) {
            merged.push_back(v1[i]);
            ++i;
        } else {
            merged.push_back(v2[j]);
            ++j;
        }
    }

    while (i < v1.size()) {
        merged.push_back(v1[i]);
        ++i;
    }

    while (j < v2.size()) {
        merged.push_back(v2[j]);
        ++j;
    }

    Stack<T> result;
    for (auto it = merged.rbegin(); it != merged.rend(); ++it) {
        result.push(*it);
    }

    return result;
}

#endif
