#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

template <typename T> void interleaveHalves(Stack<T>& stack) {
    if (stack.size() <= 1)
        return;

    int n = stack.size();
    int mid = n / 2;

    Stack<T> tmp = stack;
    std::vector<T> v;


    while (!tmp.isEmpty()) {
        v.push_back(tmp.top());
        tmp.pop();
    }

    std::vector<T> topHalf;
    std::vector<T> bottomHalf;


    for (int i = 0; i < n; i++) {
        if (i < mid)
            topHalf.push_back(v[i]);
        else
            bottomHalf.push_back(v[i]);
    }


    std::vector<T> mix;
    int a = bottomHalf.size();
    int b = topHalf.size();
    int m = std::max(a, b);

    for (int i = 0; i < m; i++) {
        if (i < a) mix.push_back(bottomHalf[i]);
        if (i < b) mix.push_back(topHalf[i]);
    }


    while (!stack.isEmpty())
        stack.pop();


    for (auto& x : mix)
        stack.push(x);
}


// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T>
std::vector<T> nextGreaterElement(Stack<T> stack) {



    while (!stack.isEmpty()) {
        temp.push_back(stack.top());
        stack.pop();
    }


    for (int i = temp.size() - 1; i >= 0; i--)
        v.push_back(temp[i]);

    int n = v.size();
    std::vector<T> res(n, -1);


    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (v[j] > v[i]) {
                res[i] = v[j];
                break;
            }
        }
    }


    return res;
}


} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
