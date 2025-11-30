#include "StackQuestionsNonMember.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
using namespace std;
namespace StackUtils {

// ============================================================================
// Question 4: Simplify Unix Path
// ============================================================================
string simplifyPath(const string &path) {
  	vector<string> stack;
	stringstream ss(path);
    string part;
    while (getline(ss, part, '/')) {
        if (part == "" || part == ".") {
            continue;
        } 
		else if (part == "..") {
            if (!stack.empty())
                stack.pop_back();
        } 
		else {
            stack.push_back(part);
        }
    }
    string result = "/";
    for (size_t i = 0; i < stack.size(); ++i) {
        result += stack[i];
        if (i + 1 < stack.size()) result += "/";
    }
    return result;
}

} // namespace StackUtils
