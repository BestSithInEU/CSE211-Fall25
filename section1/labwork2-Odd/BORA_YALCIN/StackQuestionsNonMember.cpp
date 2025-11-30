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
 
 Stack newStack = new Stack();
 char* ptr = infix;
 int i = 0;
 while(*ptr != null){
 	newStack.push(infix[i])
 	i++;
	ptr++;
 }
 char[] arr = new char[i];
 char c;
 Node* cur = newStack.topNode;
 while(cur -> next = nullptr){
 	if( cur -> data == '('){
 		
 		while(cur -> data != ')'){
 			
 			
 			
		 }
	 }
 }
 
  
}

} // namespace StackUtils
