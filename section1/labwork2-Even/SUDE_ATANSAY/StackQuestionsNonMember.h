#ifndef STACK_QUESTIONS_NON_MEMBER_H
#define STACK_QUESTIONS_NON_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

template <typename T> class Stack;

namespace StackUtils {
	template <typename T> class StackQuestions : public Stack<T> {
public:
  using Stack<T>::Stack; // Inherit constructors



void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2){
	
	 while (!stack1.isEmpty()) stack1.pop();
    while (!stack2.isEmpty()) stack2.pop();

    Stack<T> temp;

    while (!source.isEmpty()) {
        temp.push(source.top());
        source.pop();

    }

    bool toFirst = true;
    while (!temp.isEmpty()) {
        if (toFirst) {
            stack1.push(temp.top());
        } else {
            stack2.push(temp.top());
        }

        temp.pop();
        toFirst = !toFirst;

    }

  

}



std::string simplifyPath(const std::string &path){
	 stack<string> st;

     stringstream ss(path);
     string token;


    while (std::getline(ss, token, '/')) {
        if (token.empty() || token == ".") {
            continue;

        } else if (token == "..") {
            if (!st.empty()) st.pop();

        } else {
            st.push(token);

        }

    }



    if (st.empty()) return "/";
    vector<string> parts;

    while (!st.empty()) {
        parts.push_back(st.top());
        st.pop();

    }

    reverse(parts.begin(), parts.end());
    string result;
    for (const auto& p : parts) {
        result += "/" + p;

    }

    return result.empty() ? "/" : result;

}
	
	
	
	
;};};

 


#include "StackQuestionsNonMember.tpp"

#endif // STACK_QUESTIONS_NON_MEMBER_H
