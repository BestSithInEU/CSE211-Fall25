#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Split Alternate
// ============================================================================
template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
    int sayac = 0;
    while (!source.isEmpty()) {
        T deger = source.top();
        source.pop();

        if (sayac % 2 == 0) {
            stack1.push(deger);
        } else {
            stack2.push(deger);
        }

        sayac++;
    }
  }

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
