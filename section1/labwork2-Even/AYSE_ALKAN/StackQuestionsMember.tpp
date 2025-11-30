#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T> T StackQuestions<T>::findMiddle() const {
  // TODO: Implement this function
    if (this->isEmpty()) {
    throw std::underflow_error("Stack is empty: Cannot find middle element");
  }

  size_t mid = this->size() / 2;


  Stack<T> temp;
  Stack<T> copy(*this);

  while (!copy.isEmpty()) {
    temp.push(copy.top());
    copy.pop();
  }


  size_t count = 0;
  T result;
  while (!temp.isEmpty() && count <= mid) {
result = temp.top();
    temp.pop();
    count++;
  }

  return result;
}


template <typename T> void insertAtBottom(Stack<T> &stack, const T &item) {
  if (stack.isEmpty()) {
    stack.push(item);
    return;
  }

  T temp = stack.top();
  stack.pop();
  insertAtBottom(stack, item);
  stack.push(temp);
}

}

// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse() {
  // TODO: Implement this function
    if (this->isEmpty()) {
    return;
  }

  T temp = this->top();
  this->pop();
  reverse();
  insertAtBottom(*this, temp);
}

template <typename T>
void splitAlternate(Stack<T> &source, Stack<T> &stack1, Stack<T> &stack2) {
  stack1.clear();
  stack2.clear();

  Stack<T> temp;


  while (!source.isEmpty()) {
        temp.push(source.top());
    source.pop();
  }

  bool toStack1 = true;
  while (!temp.isEmpty()) {
    if (toStack1) {
      stack1.push(temp.top());
    } else {
      stack2.push(temp.top());
    }
    temp.pop();
    toStack1 = !toStack1;
  }
}


std::string simplifyPath(const std::string &path) {
  Stack<std::string> stack;
  std::stringstream ss(path);
  std::string token;

  while (std::getline(ss, token, '/')) {
    if (token.empty() || token == ".") {
      continue;
    } else if (token == "..") {
      if (!stack.isEmpty()) {
        stack.pop();
      }
    } else {
      stack.push(token);
    }
  }

  if (stack.isEmpty()) {
    return "/";
  }

  std::vector<std::string> dirs;
  while (!stack.isEmpty()) {
    dirs.push_back(stack.top());

  stack.pop();
  }

  std::string result = "";
  for (int i = dirs.size() - 1; i >= 0; --i) {
    result += "/" + dirs[i];
  }

  return result;
}


}

#endif // STACK_QUESTIONS_MEMBER_TPP

