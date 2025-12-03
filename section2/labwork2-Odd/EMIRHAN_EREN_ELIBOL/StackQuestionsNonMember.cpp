#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <stack>

namespace StackUtils {

int longestValidParentheses(const std::string &s) {
    std::stack<int> st;
    int maxLen = 0;
    st.push(-1);

    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        if (s[i] == '(') {
            st.push(i);
        } else {
            if (!st.empty()) {
                st.pop();
            }

            if (st.empty()) {
                st.push(i);
            } else {
                int len = i - st.top();
                if (len > maxLen) {
                    maxLen = len;
                }
            }
        }
    }

    return maxLen;
}

}
