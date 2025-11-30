#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace StackUtils {

// ============================================================================
// Question 4: Simplify Unix Path
// ============================================================================
std::string simplifyPath(const std::string &path) {
	
	Stack<char> simpli;
	Stack<char> simpli2;
	simpli.push('/');
	
	for(int i=0;path[i+1]!='\0';i++)
	{
		if(path[i]!='/'&&path[i]!='.')
		{
			simpli.push(path[i]);
			if(path[i+1]=='/')
				simpli.push('/');

		}
		
		if (path[i]=='.'&&path[i+1]=='.')
		{
			if(simpli.size()>1)
			{
			
				while(simpli.top()=='/')
					simpli.pop();
				simpli.pop();
		}
		}
	}
	
	int x=simpli.size()-1;
	char op[x];
	while(!simpli.isEmpty())
	{
		simpli2.push(simpli.top());
		simpli.pop();
	}
	int i=0;
	for(;!simpli2.isEmpty();i++)
	{
		op[i]=simpli2.top();
		simpli2.pop();
	}
	
	op[i-1]='\0';
	
	return op;
  // TODO: Implement this function
}

} // namespace StackUtils
