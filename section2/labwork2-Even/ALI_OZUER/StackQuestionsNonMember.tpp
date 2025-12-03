#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils template <typename T>
void interleaveHalves(Stack<T> &stack) {
  if (stack.size() <= 1)
    return;
  Stack<T> bot;
  Stack<T> top;
  int mid = stack.size() / 2;
  for (int i = 0; i < mid; i++) {
    bot.push(stack.top());
    stack.pop();
  }
  while (!stack.isEmpty()) {
    top.push(stack.top());
    stack.pop();
  }
  while (!top.isEmpty() && !bot.isEmpty()) {
    stack.push(bot.top());
    bot.pop();
    stack.push(top.top());
    top.pop();
  }
  while (!top.isEmpty()) {
    stack.push(top.top());
    top.pop();
  }
  while (!bot.isEmpty()) {
    stack.push(bot.top());
    bot.pop();
  }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  return;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
