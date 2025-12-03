#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP
using namespace std;
#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack){
// TODO: Implement Thistemplate <typename T>


template <typename T>
void StackUtils::interleaveHalves(Stack<T>& stack) {

    if (stack.size() <= 1)
        return;
    int HalfSize = (stack.size() + 1) / 2;

    Stack<T> reversed;
    Stack<T> bottom;
    Stack<T> top;
    Stack<T> result;

    while (!stack.isEmpty()) {
        reversed.push(stack.top());
        stack.pop();
    }


    for (int i = 0; i < HalfSize; i++) {
        bottom.push(reversed.top());
        reversed.pop();}

    while (!reversed.isEmpty()) {
        top.push(reversed.top());
        reversed.pop();
    }


    while (!bottom.isEmpty() & !top.isEmpty()) {
        result.push(bottom.top());
        bottom.pop();
        result.push(top.top());
        top.pop();}

    while(!bottom.isEmpty()) {
        result.push(bottom.top());
        bottom.pop();}

    while (!result.isEmpty()) {
        stack.push(result.top());
        result.pop();
    }
}

}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  // TODO: Implement This



  //YazamadÄ±m :(
}

}// namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
