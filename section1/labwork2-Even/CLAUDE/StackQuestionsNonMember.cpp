#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <vector>

namespace StackUtils {

// ============================================================================
// Question 4: Simplify Unix Path
// ============================================================================
std::string simplifyPath(const std::string &path) {
  std::vector<std::string> stack;
  std::string token = "";

  for (size_t i = 0; i <= path.size(); i++) {
    if (i == path.size() || path[i] == '/') {
      if (token == "..") {
        if (!stack.empty()) {
          stack.pop_back();
        }
      } else if (!token.empty() && token != ".") {
        stack.push_back(token);
      }
      token = "";
    } else {
      token += path[i];
    }
  }

  std::string result = "";
  for (size_t i = 0; i < stack.size(); i++) {
    result += "/" + stack[i];
  }

  return result.empty() ? "/" : result;
}

} // namespace StackUtils
