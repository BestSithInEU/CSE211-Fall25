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
	Stack<char> stack;
	std::string out;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix.at(i) >= '0' && infix.at(i) <= '9')
			out += infix.at(i);
		else if (infix.at(i) == '(')
			stack.push(infix.at(i));
		else if (infix.at(i) == ')')
		{
			while (!stack.isEmpty())
			{
				if (stack.top() == '(')
					break;
				out += stack.top();
				stack.pop();
			}
			if (!stack.isEmpty())
				stack.pop();
		}
		else if (isOperator(infix.at(i)))
		{
			if (precedence(infix.at(i)) < precedence(stack.top()))
			{
				while (!stack.isEmpty())
				{
					out += stack.top();
					stack.pop();
				}
			}
		}
		else
			continue;
	}
	return out;
}
	
} // namespace StackUtils
