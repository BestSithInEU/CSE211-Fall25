#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

template <typename T>
Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
    Stack<T> copy1 = stack1;
    Stack<T> copy2 = stack2;
    Stack<T> sorted_temp;
    Stack<T> sorted;

    while (!copy1.isEmpty() && !copy2.isEmpty()) {
        if (copy1.top() > copy2.top()) {
            sorted_temp.push(copy2.top());
            copy2.pop();
        } else {
            sorted_temp.push(copy1.top());
            copy1.pop();
        }
    }

    while (!copy1.isEmpty()) {
        sorted_temp.push(copy1.top());
        copy1.pop();
    }

    while (!copy2.isEmpty()) {
        sorted_temp.push(copy2.top());
        copy2.pop();
    }

    while (!sorted_temp.isEmpty()) {
        sorted.push(sorted_temp.top());
        sorted_temp.pop();
    }

    return sorted;
}

}

#endif