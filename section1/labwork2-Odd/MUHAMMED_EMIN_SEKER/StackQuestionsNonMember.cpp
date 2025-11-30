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
static bool isDigit(char x){
	if(x >='0'&& x<='9')
		return true;
}

// ============================================================================
// Question 4: Infix to Postfix Conversion
// ============================================================================
std::string infixToPostfix(const std::string &infix) {
  // TODO: IMPLEMENTATION
  Stack<T> temp,t1,t2,t3,t4;
  temp->clear();
  for(char c : infix){
  	temp.push(c);
  }
  char p[100];
  while(!temp.isEmpty()){
  	t1.push(temp.top());
  	temp.pop();
  }// Temp i ters çevirdik (stringdeki sýraya)

   
  
  while(!t1->isEmpty()&& t1.top()!='('){
  	if(isDigit(t1.top())){
  		T val1=t1.top();
  		t1.pop();
	  }
  	
  	if(isOperator(t1.top())){
  		
  		if(precedence(t1.top())==2){
  			T op =t1.top();
  			t1.pop();
  			T val2=t1.top();
  			t1.pop();
		  }
		else{
			T op =t1.top();
  			t1.pop();
  			T val2=t1.top();
  			t1.pop();
			
		}
		t2.push(val1);
		t2.push(val2);
		t2.push(op);
	  }
  	
  }
  if(!t1.isEmpty()){// parantez açýldý
  	
  	while(!t1->isEmpty()&& t1.top()!=')'){
  		if(isDigit(t1.top())){
  			T val1=t1.top();
  			t1.pop();
	  	}
  	
  		if(isOperator(t1.top())){
  		
  			if(precedence(t1.top())==2){
  				T op =t1.top();
  				t1.pop();
  				T val2=t1.top();
  				t1.pop();
		 	 }
			else{
				T op =t1.top();
  				t1.pop();
  				T val2=t1.top();
  				t1.pop();
			
			}
			t3.push(val1);
			t3.push(val2);
			t3.push(op);
	  }
	  }
  }
  while(!t2.isEmpty()){
  	t4.push(t2.top());
  	t2.pop();
  }
  while(!t4.isEmpty()){
  	t3.push(t4.top());
  	t4.pop();
  }
  while(!t3.isEmpty()){
  	t4.push(t3.top());
  	t3.pop();
  }
  // son olarak stacktekileri stringe eklemek kalýyor
  		
  	

  }


} // namespace StackUtils


/*

infix1 = "3 + 4 * 2";

Output: "3 4 2 * +"
// Explanation: Multiplication has higher precedence
 infix2 = "( 5 + 1 ) * 4 - 3";

Output: "5 1 + 4 * 3 -"
 Explanation: Parentheses force addition first


*/
