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
  std::stringstream ss(infix);
  std::stringstream output;
  std::stack<char> ops;

  std::string token;
  while (ss >> token) {
    // If operand (number)
    if (isdigit(token[0])) {
      output << token << " ";
    } else if (token == "(") {
      ops.push('(');
    } else if (token == ")") {
      while (!ops.empty() && ops.top() != '(') {
        output << ops.top() << " ";
        ops.pop();
      }
      ops.pop(); // remove '('
    } else if (token.size() == 1 && isOperator(token[0])) {
      char op = token[0];
      while (!ops.empty() && isOperator(ops.top()) &&
             precedence(ops.top()) >= precedence(op)) {
        output << ops.top() << " ";
        ops.pop();
      }
      ops.push(op);
    }
  }

  // Pop remaining operators
  while (!ops.empty()) {
    output << ops.top() << " ";
    ops.pop();
  }

  std::string res = output.str();
  if (!res.empty() && res.back() == ' ')
    res.pop_back();
  return res;
}

} // namespace StackUtils
