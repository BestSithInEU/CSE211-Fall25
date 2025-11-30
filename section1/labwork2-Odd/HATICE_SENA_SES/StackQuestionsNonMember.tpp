#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Is Subsequence
// ============================================================================
template <typename T>
bool isSubsequence(const Stack<T> &mainStack, const Stack<T> &potential) {
  // TODO: IMPLEMENTATION
  void isSubsequence() {
  
  isEmpty(stack, *s){
  	return;
  }

  Stack<int> mainStack;
  mainStack.loadFromJSON("examples/nonmembers.json", "q3_main");

  Stack<int> subseq1;
  subseq1.loadFromJSON("examples/nonmembers.json", "q3_subseq1");

  Stack<int> subseq2;
  subseq2.loadFromJSON("examples/nonmembers.json", "q3_subseq2");

  printInfo("Main stack (top to bottom): 5, 4, 3, 2, 1");
  printInfo("Subsequence 1: 4, 2");
  std::cout << "Is subsequence? "
            << (StackUtils::isSubsequence(mainStack, subseq1) ? "Yes" : "No")
            << std::endl;

  printInfo("Subsequence 2: 2, 4 (reversed)");
  std::cout << "Is subsequence? "
            << (StackUtils::isSubsequence(mainStack, subseq2) ? "Yes" : "No")
            << std::endl;
}
}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
