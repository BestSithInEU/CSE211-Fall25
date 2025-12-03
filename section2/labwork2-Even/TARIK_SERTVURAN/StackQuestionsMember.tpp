#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This

  if(this->isEmpty()){
    return 0 ;
  }

  std::vector<T> vec;
  Stack<T> temp = *this;


  while (!temp.isEmpty()){
    T value = temp.top();
    temp.pop();
    vec.push_back(value);
  }

  if (vec.size() == 1) {
    return 1;
  }

  int currentLength = 1;
  int maxLength = 1;

  for ( int i = 0 ; i < vec.size()- 1 ; i++) {
    T x = vec[i];
    T y = vec [i+1];

    if ( x-y == 1 || y-x == 1) {
        currentLength++;
    }
    else {
        currentLength=1;
    }

    if(currentLength>maxLength){
        maxLength = currentLength;
    }
  }
  return maxLength;

}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
    if (this->isEmpty()){
        return ;
    }

    Stack<T> temp = *this;
    std::vector<T> vec;

    while (!temp.isEmpty()){
    T value = temp.top();
    temp.pop();
    vec.push_back(value);
  }

  int n = vec.size();


  k = k%n;

  if(k<0){
    k = k+n;
  }

  if (k == 0) {
    return;
  }

  std::vector<T> rotated;
  rotated.resize(n);

  for(int i = 0; i<n ;i++){
    int newindex = (i+k)% n ;
    rotated[newindex] = vec[i];
  }

    while(!this->isEmpty()){
        this->pop();
    }

    for( int i = 0 ; i<n; i ++){
        this->push(rotated[i]);
    }


}

#endif // STACK_QUESTIONS_MEMBER_TPP
