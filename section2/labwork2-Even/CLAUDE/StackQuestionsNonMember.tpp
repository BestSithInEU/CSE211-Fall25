#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: interleaveHalves
// ============================================================================
template <typename T>
void interleaveHalves(Stack<T> &stack) {
  if (stack.isEmpty()) {
    return;
  }

  size_t n = stack.size();
  if (n < 2) {
    return;
  }

  size_t half = n / 2;

  // Move all elements to aux (reversed)
  Stack<T> aux;
  while (!stack.isEmpty()) {
    aux.push(stack.top());
    stack.pop();
  }

  // aux now has elements in reversed order (bottom->top becomes top->bottom)
  // Split into first half and second half
  Stack<T> firstHalf;
  Stack<T> secondHalf;

  // First half elements (top half of original)
  for (size_t i = 0; i < half; i++) {
    firstHalf.push(aux.top());
    aux.pop();
  }

  // Second half elements (bottom half of original)
  while (!aux.isEmpty()) {
    secondHalf.push(aux.top());
    aux.pop();
  }

  // Reverse firstHalf and secondHalf to get correct order
  Stack<T> first, second;
  while (!firstHalf.isEmpty()) {
    first.push(firstHalf.top());
    firstHalf.pop();
  }
  while (!secondHalf.isEmpty()) {
    second.push(secondHalf.top());
    secondHalf.pop();
  }

  // Interleave: take from second, then first alternately
  // Build result in aux, then reverse back to stack
  while (!first.isEmpty() || !second.isEmpty()) {
    if (!second.isEmpty()) {
      aux.push(second.top());
      second.pop();
    }
    if (!first.isEmpty()) {
      aux.push(first.top());
      first.pop();
    }
  }

  // Reverse aux back to stack
  while (!aux.isEmpty()) {
    stack.push(aux.top());
    aux.pop();
  }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {
  std::vector<T> elements;
  std::vector<T> result;

  // Extract all elements from stack (will be in reverse order)
  while (!stack.isEmpty()) {
    elements.push_back(stack.top());
    stack.pop();
  }

  // elements[0] is top of stack, elements[n-1] is bottom
  // We want next greater for each element looking towards the top
  // So we process from bottom to top (reverse order)

  size_t n = elements.size();
  result.resize(n);

  Stack<T> mono; // monotonic stack to track greater elements

  // Process from bottom to top of original stack
  for (int i = n - 1; i >= 0; i--) {
    T curr = elements[i];

    // Pop elements smaller than or equal to current
    while (!mono.isEmpty() && mono.top() <= curr) {
      mono.pop();
    }

    // If stack is empty, no greater element exists
    if (mono.isEmpty()) {
      result[i] = T(-1);
    } else {
      result[i] = mono.top();
    }

    mono.push(curr);
  }

  // Result is in order from top to bottom, reverse to match expected output
  std::reverse(result.begin(), result.end());
  return result;
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
