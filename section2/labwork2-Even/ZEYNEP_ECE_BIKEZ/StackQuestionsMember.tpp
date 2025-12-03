#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  std::vector<T> vector1;
  int count = 0;
  int maxCount = 1;
  StackQuestions<T> copy = *this;

    if(copy.isEmpty()){
        return 0;
    }
  while(!copy.isEmpty()){
    vector1.push_back(copy.top());
    copy.pop();
  }

  if(vector1.size() == 1){
    return 1;
  }
  for(int i = 0; i < vector1.size() ; i++){
    if(vector1[i] + 1 == vector1[i+1] ||vector1[i] - 1 == vector1[i+1] ){
        count++;
        if(count > maxCount){
            maxCount = count;
        }
    }
    else{
        count = 1;
    }
    }
  return maxCount + 1;

}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
    std::vector<T> vector2;
    int count = 0;
    if(this->isEmpty()){
        return ;
    }
    if(vector2.size() == 1){
        return;
    }
    StackQuestions<T> copy = *this;
    while(!copy.isEmpty()){
        vector2.push_back(copy.top());
        copy.pop();
    }

    if(k > 0){
        while(count < k){
            T temp = vector2.back();
            vector2.pop_back();
            vector2.insert(vector2.begin(),temp);
            count++;
        }
    }
    if(k < 0){
        while(count < -k){
            T temp = vector2.front();
            vector2.erase(vector2.begin());
            vector2.push_back(temp);
            count++;
        }
    }
    this->clear();
    for(int i = vector2.size(); i>=0; i++){
        this->push(vector2[i]);
    }

}

#endif // STACK_QUESTIONS_MEMBER_TPP
