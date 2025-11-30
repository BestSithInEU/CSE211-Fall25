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
stack<char> temp;
std::string ret;
char a;
for(int i=0;i<path.lenght();i++){
	if(path[i]=='/'){
		if(path[i+1]=='.'){
			if(path[i+2]=='.'){
				temp.pop();
			}
			else{
				temp.push(path[i]);
				i+=1;
			}
		}
		
		if(path[i+1]=='/'){
			continue;
		}
		else{
			temp.push(path[i]);
		}
	}
	else{
		temp.push(path[i]);
	}
	
}
while(!temp.isEmpty()){
	a=temp.top();
	temp.pop();
	ret=ret+a;
	
}
return ret;


}

} // namespace StackUtils
