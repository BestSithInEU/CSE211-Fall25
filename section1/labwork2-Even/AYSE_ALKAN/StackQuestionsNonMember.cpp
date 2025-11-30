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
    // TODO: Implement this function
    
    
std::stringstream ss(path);
std::string segment;
std::stack<std::string> dirStack;
  
  
  while (std::getline(ss, segment, '/')) {
if (segment == "..") {
if (!dirStack.empty()) {
dirStack.pop();
}
} else {

dirStack.push(segment);
}
} 
if (dirStack.empty()) {
return "/"; 
} 
std::vector<std::string> pathComponents;
  
  while (!dirStack.empty()) {
pathComponents.push_back(dirStack.top());
dirStack.pop();
}
std::reverse(pathComponents.begin(), pathComponents.end());
std::string canonicalPath = "";

for (const std::string& component : pathComponents) {
thePath += "/" + component;
}
 return thePath;

}

} // namespace StackUtils
