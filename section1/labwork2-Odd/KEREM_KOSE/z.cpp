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
  char c;
  int num1;
  int num2;
  int result=0;
  std:cout<<"choose the operation type(+,-,*,/)"<<;
  std:cin>>c>>;
  std:cout<<"choose the number 1"<<;
  std:cin>>num1>>;
  std:cout<<"choose the number 2"<<;
  std:cin>>num2>>;
  
  if (precedence==0){
  	std:cout<<"unknown operation type"<<;
  	std:cout<<"choose the operation type(+,-,*,/)"<<;
	std:cin>>c>>;
}
  
  if (precedence==1){
  	if(isOperator(c)==+){
  	result = num1 + num2;
  	cout<<"result:"+result<<
  } 
  if(isOperator(c)==-){
  	result = num1 - num2;
  	cout<<"result:"+result<<
  }
  }
  if (precedence==2){
  	if(isOperator(c)==*){
  	result = num1 * num2;
  	cout<<"result:"+result<<
  }
  if(isOperator(c)==/){
  	result = num1 / num2;
  	cout<<"result:"+result<<
  }
  }
  
}

} // namespace StackUtils
