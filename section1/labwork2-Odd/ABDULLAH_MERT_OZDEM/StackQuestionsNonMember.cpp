// StackQuestionsNonMember.cpp
// Contains Q4 solution

namespace StackUtils {

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    std::stringstream ss(infix);
    std::string token;
    std::string output = "";
    Stack<std::string> ops;

    while (ss >> token) {
        if (isdigit(token[0])) {
            output += token + " ";
        }
        else if (token == "(") {
            ops.push(token);
        }
        else if (token == ")") {
            while (!ops.isEmpty() && ops.top() != "(") {
                output += ops.top() + " ";
                ops.pop();
            }
            ops.pop();
        }
        else {
            while (!ops.isEmpty() &&
                precedence(ops.top()[0]) >= precedence(token[0])) {
                output += ops.top() + " ";
                ops.pop();
            }
            ops.push(token);
        }
    }

    while (!ops.isEmpty()) {
        output += ops.top() + " ";
        ops.pop();
    }

    if (!output.empty()) output.pop_back();

    return output;
}

} // namespace StackUtils
