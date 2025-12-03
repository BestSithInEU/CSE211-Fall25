#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>


namespace StackUtils {

int longestValidParentheses(const std::string &s) {
  Stack<int> st;
  st.push(-1);
  int maxLength = 0;
  
  for (int i = 0; i < (int)s.length(); i++) {
    if (s[i] == '(') {
      st.push(i);
    } else {
      st.pop();
      
      if (st.isEmpty()) {
        st.push(i);
      } else {
        int currentLength = i - st.top();
        if (currentLength > maxLength) {
          maxLength = currentLength;
        }
      }
    }
  }
  
  return maxLength;
}

} // namespace StackUtils
