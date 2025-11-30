#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // Empty stack is subsequence of any stack
  if (potential.isEmpty()) {
    return true;
  }

  // Convert stacks to vectors for traversal (top-to-bottom order)
  std::vector<T> mainVec;
  std::vector<T> potVec;

  Stack<T> mainCopy = mainStack;
  Stack<T> potCopy = potential;

  while (!mainCopy.isEmpty()) {
    mainVec.push_back(mainCopy.top());
    mainCopy.pop();
  }

  while (!potCopy.isEmpty()) {
    potVec.push_back(potCopy.top());
    potCopy.pop();
  }

  // Two-pointer matching
  size_t mainIdx = 0;
  size_t potIdx = 0;

  while (mainIdx < mainVec.size() && potIdx < potVec.size()) {
    if (mainVec[mainIdx] == potVec[potIdx]) {
      potIdx++;
    }
    mainIdx++;
  }

  return potIdx == potVec.size();
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
