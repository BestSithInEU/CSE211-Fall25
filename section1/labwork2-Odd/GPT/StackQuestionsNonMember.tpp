#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  if (potential.size() == 0)
    return true;

  // Copy stacks into vectors (top â†’ bottom)
  std::vector<T> mainVec;
  std::vector<T> potVec;

  {
    std::stack<T> ms = mainStack.getInternal();
    while (!ms.empty()) {
      mainVec.push_back(ms.top());
      ms.pop();
    }
  }
  {
    std::stack<T> ps = potential.getInternal();
    while (!ps.empty()) {
      potVec.push_back(ps.top());
      ps.pop();
    }
  }

  // Two-pointer match
  size_t i = 0, j = 0;
  while (i < mainVec.size() && j < potVec.size()) {
    if (mainVec[i] == potVec[j])
      j++;
    i++;
  }

  return j == potVec.size();
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
