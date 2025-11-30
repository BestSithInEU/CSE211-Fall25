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
  
  void demo_infixToPostfix() {
  printHeader("Q4: infixToPostfix()");

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

}

} // namespace StackUtils
