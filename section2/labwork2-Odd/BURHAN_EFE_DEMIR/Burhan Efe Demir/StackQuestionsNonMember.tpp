#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Merge Sorted Stacks
// ============================================================================
template <typename T> Stack<T> mergeSorted(Stack<T> &stack1, Stack<T> &stack2) {
  // TODO: Implementation

  // orijinalleri bozmamak icin kopyalarla calisiyoruz
  Stack<T> s1 = stack1;
  Stack<T> s2 = stack2;

  // siralamayi yaparken once buraya atacagiz (ters siralanacak)
  Stack<T> tmp;

  // iki stack de dolu oldugu surece
  while (!s1.isEmpty() && !s2.isEmpty()) {
    if (s1.peek() < s2.peek()) {
        tmp.push(s1.peek());
        s1.pop();
    }
    else {
        tmp.push(s2.peek());
        s2.pop();
    }
    }

    // biri bitti ama digerinde eleman kaldiysa onlari da ekliyorum
    while (!s1.isEmpty()) {
        tmp.push(s1.peek());
        s1.pop();
    }
    while (!s2.isEmpty()) {
        tmp.push(s2.peek());
        s2.pop();
    }

    // su an tmp icinde sayilar en kucuk en dipte olacak sekilde duruyor
    // bunlari result stack'ine akatrip duzelticez

    Stack<T> result;
    while (!tmp.isEmpty()){
        result.push(tmp.peek());
        tmp.pop();
    }

    return result;
  }
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
