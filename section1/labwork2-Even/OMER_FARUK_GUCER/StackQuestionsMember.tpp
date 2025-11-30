#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
   if (isEmpty()) {
        return T();
    }

    int sayi = size();
    int ortasayi = sayi / 2;

    return getKthFromTop(ortasayi);
}
}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
    Stack<T> gecicist1;
    Stack<T> gecicist2;

    while (!isEmpty()) {
        gecicist.push(top());
        pop();
    }

    while (!gecicist1.isEmpty()) {
        gecicist2.push(gecicist1.top());
        gecicist1.pop();
    }

    while (!gecicist2.isEmpty()) {
        push(gecicist2.top());
        gecicist2.pop();
    }
  }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
