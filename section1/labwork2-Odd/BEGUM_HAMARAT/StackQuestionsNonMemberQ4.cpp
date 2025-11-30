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
	std::stack <char> ops;
	std::stringStream output;
	
	for(size_t i=0 ; infix.size() ; i++){
		if(std:: isdigit(infix[i])) {
			std:: string num;
			while(i< infix.size() && std::isdigit(infix[i])) {
				num+= infix[i];
				i++;
			} 
			output << num << "";
			i--;
		}
		
		else if( infix[i] == '(') {
			ops.push(infix[i]);
		}
		
		else if(infix[i] == ')' ) {
			while(!ops.empty() && ops.top() != '(') {
				output << ops.top() << "";
				ops.pop();
			}
			if(!ops.empty())
			   ops.pop();
		}
		
		else{
			while(!ops.empty() && precedence(ops.top()) >= precedence(infix[i])) {
				output << ops.top() << "";
				ops.pop();
			}
			ops.push(infix[i]);
		}
	} 
	
	while(!ops.empty() {
		output << ops.top() << "";
		ops.pop();
	}
	
	return output.str();
}

} // namespace StackUtils














