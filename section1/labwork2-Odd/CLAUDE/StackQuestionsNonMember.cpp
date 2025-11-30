#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
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
  Stack<char> opStack;
  std::string result;
  size_t i = 0;

  while (i < infix.length()) {
    // Skip whitespace
    if (std::isspace(infix[i])) {
      i++;
      continue;
    }

    // Check for number (multi-digit supported)
    if (std::isdigit(infix[i])) {
      if (!result.empty())
        result += " ";
      while (i < infix.length() && std::isdigit(infix[i])) {
        result += infix[i];
        i++;
      }
    } else if (infix[i] == '(') {
      // Left parenthesis: push to stack
      opStack.push('(');
      i++;
    } else if (infix[i] == ')') {
      // Right parenthesis: pop until matching left parenthesis
      while (!opStack.isEmpty() && opStack.top() != '(') {
        if (!result.empty())
          result += " ";
        result += opStack.top();
        opStack.pop();
      }
      if (!opStack.isEmpty())
        opStack.pop(); // Remove '('
      i++;
    } else if (isOperator(infix[i])) {
      // Operator: pop higher/equal precedence operators first
      while (!opStack.isEmpty() && opStack.top() != '(' &&
             precedence(opStack.top()) >= precedence(infix[i])) {
        if (!result.empty())
          result += " ";
        result += opStack.top();
        opStack.pop();
      }
      opStack.push(infix[i]);
      i++;
    } else {
      i++;
    }
  }

  // Pop remaining operators
  while (!opStack.isEmpty()) {
    if (!result.empty())
      result += " ";
    result += opStack.top();
    opStack.pop();
  }

  return result;
}

} // namespace StackUtils
