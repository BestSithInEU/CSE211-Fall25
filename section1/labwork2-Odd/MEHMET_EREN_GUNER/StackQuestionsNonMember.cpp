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
std::string infixToPostfix(const std::string &infix){
  Stack<char> stack;
  std::string result;
  std::stringstream ss(infix);
  std::string token;
  
  while (ss >> token) {
    if (isdigit(token[0])) {
    
      result += token + " ";
    
    }
    else if (token[0] == '(') {
      stack.push('(');
    }
    else if (token[0] == ')') {
      while (!stack.isEmpty() && stack.top() != '(') {
        result += stack.top();
        result += " ";
        stack.pop();
      }
      stack.pop();
    }
    else if (isOperator(token[0])) {
      while (!stack.isEmpty() && stack.top() != '(' && 
             precedence(stack.top()) >= precedence(token[0])){
        result += stack.top();
        result += " ";
        stack.pop();
      }
      stack.push(token[0]);
    }
  }
  
  while (!stack.isEmpty()) {
    result += stack.top();
    result += " ";
    stack.pop();
  }
  
  if (!result.empty() && result.back() == ' '){
    result.pop_back();
  } 
  return result;
}

} // namespace StackUtils
