#define STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP
#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: findMiddle
// ============================================================================
template <typename T>
T StackQuestions<T>::findMiddle() const {
  if (stack.empty()) {
        throw "ERROR::findMidle():Stack is empty";
    }
    size_t middleIndex = (size() - 1) / 2;
    return stack[middleIndex];
}


// ============================================================================
// Question 2: reverse
// ============================================================================
template <typename T> void StackQuestions<T>::reverse(){
    if (isEmpty()){
        throw "list is empty!!";
    }
    T topElement = pop();
    reverse();
    StackQuestions<T> tempStack;
    while (!isEmpty()) {
        tempStack.push(pop());
    }
    while (!tempStack.isEmpty()) {
        push(tempStack.pop());
    }
    push(topElement);
}


#endif // STACK_QUESTIONS_MEMBER_TPP
