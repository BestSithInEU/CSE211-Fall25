#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: longestConsecutiveSequence
// ============================================================================
template <typename T>
size_t StackQuestions<T>::longestConsecutiveSequence() const {
  // TODO: Implement This
  if(stack.empty()){return 0;}
  if(stack.size() == 1){return 1};
  std::stack<T> stack2 = stack;
  std::vector<T>data;
  while (!stack2.empty()){
    T topdeg=stack2.top();
    data.push(topdeg));
    stack2.pop();

}
int big,cur;
for(int i=0; i<size;i++){
    T a= data[i];
    T b= data[i+1];
    if(b-a == 1 || b-a == -1){
        cur=cur+1;
    }
    else{
        cur=1;

    }
    if(cur>big){
        big =cur;
    }
}
return big;
}

// ============================================================================
// Question 2: rotateStack
// ============================================================================
template <typename T> void StackQuestions<T>::rotateStack(int k) {
  // TODO: Implement This
  if(stack.empty()){return 0;}
  if(stack.size() == 1)return 1;
  int n = stack.size();

  int *p = &k;
  *p = *p %n;

  if(*p < 0){
    *p = *p+n;

  }
  std::stack<T> stackcopy=stack;
  std::stack<T> *sp = &stackcopy;
  std::vector<T> temp;
  while(!sp->empty()){
    T toplist = sp->top();
    temp.push(toplist);
    sp->pop();
  }
  std::vector<T>arr(n);
  for(int i = 0; i<n; i++){
    int new = i + *p;
    if(new >= n){
        new = new % n;
    }
    arr[new] = temp[i];
  }
  while(!stack.empty()){
    stack.pop();
  }
  for(int i= 0; i<n; i++){
    stack.push(arr[i]);
  }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
