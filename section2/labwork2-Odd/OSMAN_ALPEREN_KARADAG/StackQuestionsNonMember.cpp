#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace StackUtils {

int longestValidParentheses(const std::string &s) {
 int maxLength = 0;
 Stack<int> indexStack;
 indexStack.push(-1);
 
 for (int i = 0; i < (int)s.length(); ++i) {
    if (s[i] == '(') {
      indexStack.push(i);
    } else {
      indexStack.pop();
	 if (indexStack.isEmpty()) {
         indexStack.push(i);
       } else {
         maxLength = std::max(maxLength, i - indexStack.top());
      }
    }
  }

  return maxLength;
}
} // namespace StackUtils
