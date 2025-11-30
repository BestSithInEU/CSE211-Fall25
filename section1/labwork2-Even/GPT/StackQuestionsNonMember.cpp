#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace StackUtils {

// ============================================================================
// Question 4: Simplify Unix Path
// ============================================================================
std::string StackUtils::simplifyPath(const std::string &path) {
  std::stringstream ss(path);
  std::string token;
  std::vector<std::string> st; // allowed; problem says "use stack logic"

  while (std::getline(ss, token, '/')) {
    if (token == "" || token == ".")
      continue;

    if (token == "..") {
      if (!st.empty())
        st.pop_back();
    } else {
      st.push_back(token);
    }
  }

  if (st.empty())
    return "/";

  std::string result;
  for (const auto &dir : st)
    result += "/" + dir;

  return result;
}

} // namespace StackUtils
