#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  if (potential.isEmpty()) {
    return true;
  }

  Stack<T> mainCopy(mainStack);
  Stack<T> subseqCopy(potential);

  std::vector<T> mainVec;
  std::vector<T> subseqVec;

  while (!mainCopy.isEmpty()) {
    mainVec.push_back(mainCopy.top());
    mainCopy.pop();
  }

  while (!subseqCopy.isEmpty()) {
    subseqVec.push_back(subseqCopy.top());
    subseqCopy.pop();
  }

  if (subseqVec.size() > mainVec.size()) {
    return false;
  }

  size_t mainIdx = 0;
  size_t subseqIdx = 0;

  while (mainIdx < mainVec.size() && subseqIdx < subseqVec.size()) {
    if (mainVec[mainIdx] == subseqVec[subseqIdx]) {
      ++subseqIdx;
    }
    ++mainIdx;
  }

  return subseqIdx == subseqVec.size();
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
