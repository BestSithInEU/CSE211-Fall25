#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace StackUtils {

// ============================================================================
// Helper functions for expression evaluation
// ============================================================================

static int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

static bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

// ============================================================================
// Question 4: Infix to Postfix Conversion
// ============================================================================
std::string infixToPostfix(const std::string &infix) {
  // TODO: IMPLEMENTATION
  void demo_isSubsequence() {
  

  Stack<int> mainStack;
  mainStack.loadFromJSON("examples/nonmembers.json", "q3_main");

  Stack<int> subseq1;
  subseq1.loadFromJSON("examples/nonmembers.json", "q3_subseq1");

  Stack<int> subseq2;
  subseq2.loadFromJSON("examples/nonmembers.json", "q3_subseq2");
  
  isEmpty(stack, *s){
  	return;
  }
  
  

  printInfo("Main stack (top to bottom): 5, 4, 3, 2, 1");
  printInfo("Subsequence 1: 4, 2");
  std::cout << "Is subsequence? "
            << (StackUtils::isSubsequence(mainStack, subseq1) ? "Yes" : "No")
            << std::endl;

  printInfo("Subsequence 2: 2, 4 (reversed)");
  std::cout << "Is subsequence? "
            << (StackUtils::isSubsequence(mainStack, subseq2) ? "Yes" : "No")
            << std::endl;
  printSuccess("isSubsequence() works correctly!");
}

void infixToPostfix() {

  std::string infix1 = loadStringFromJSON("examples/nonmembers.json",
                                          "q4_expressions", "infix1");
  std::string infix2 = loadStringFromJSON("examples/nonmembers.json",
                                          "q4_expressions", "infix2");

  printInfo("Infix 1: \"3 + 4 * 2\"");
  std::cout << "Postfix: \"" << StackUtils::infixToPostfix(infix1) << "\""
            << std::endl;

  printInfo("Infix 2: \"( 5 + 1 ) * 4 - 3\"");
  std::cout << "Postfix: \"" << StackUtils::infixToPostfix(infix2) << "\""
            << std::endl;

  printSuccess("infixToPostfix() works correctly!");

}

} // namespace StackUtils
