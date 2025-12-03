#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

//------------------------------
//Q4: Longest Valid Parentheses
//------------------------------
namespace StackUtils {

int longestValidParentheses(const std::string &s) {
  
  std::stack<int> st;
	st.push(-1);
	
	int maxLen = 0;
	
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			st.push(i);
		} else {
			st.pop();
			
			if (st.empty()) {
				st.push(i);
			} else {
				maxLen = std::max(maxLen, i - st.top());
			}
		}
	}
	return maxLen;
}
  
}

} // namespace StackUtils
