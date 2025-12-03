#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  if (data.empty()) {
    return 0;
  }

  std::vector<T> elements;
  std::stack<T> temp = data;

  while (!temp.empty()) {
    elements.push_back(temp.top());
    temp.pop();
  }

  size_t max_Length = 1;
  size_t cur_Length = 1;


  for (size_t i = 0; i < elements.size() - 1; i++) {

    if (elements[i + 1] == elements[i] - 1) {
    cur_Length++;
    } else {
      max_Length = std::max(max_Length, cur_Length);
      cur_Length = 1;
    }
  }

  max_Length = std::max(max_Length, cur_Length);

  return max_Length;
}



// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
    if (data.empty() || k == 0) {
    return;
  }


  size_t stackSize = data.size();


  k = k % static_cast<int>(stackSize);
  if (k < 0) {
    k += stackSize;
  }


  std::vector<T> elements;
  while (!data.empty()) {
    elements.push_back(data.top());
    data.pop();
  }


  std::reverse(elements.begin(), elements.end());


  std::rotate(elements.begin(), elements.end() - k, elements.end());


  for (int i = elements.size() - 1; i >= 0; i--) {
    data.push(elements[i]);
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
