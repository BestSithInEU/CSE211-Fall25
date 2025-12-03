#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace StackUtils {

int longestValidParentheses(const std::string &s) {
  std::stack<int> st;
  st.push(-1);
  int best = 0;

  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == '(') {
      st.push(i);
    } else {
      st.pop();
      if (st.empty()) {
        st.push(i);
      } else {
        best = std::max(best, i - st.top());
      }
    }
  }

  return best;
}
} // namespace StackUtils

// namespace StackUtils
