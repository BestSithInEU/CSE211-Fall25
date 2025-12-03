#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stack>
#include <stdexcept>

namespace StackUtils {

int longestValidParentheses(const std::string &s) {
  std::stack<int> stk;
  stk.push(-1);
  int maxLen = 0;

  for (int i = 0; i < static_cast<int>(s.length()); i++) {
    if (s[i] == '(') {
      stk.push(i);
    } else {
      stk.pop();
      if (stk.empty()) {
        stk.push(i);
      } else {
        maxLen = std::max(maxLen, i - stk.top());
      }
    }
  }

  return maxLen;
}
} // namespace StackUtils

// namespace StackUtils
