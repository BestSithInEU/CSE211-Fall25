#ifndef STACK_QUESTIONS_NON_MEMBER_TPP
#define STACK_QUESTIONS_NON_MEMBER_TPP

#include "StackQuestionsNonMember.h"

namespace StackUtils {

// ============================================================================
// Question 3: Interleave Halves
// ============================================================================
template <typename T> void interleaveHalves(Stack<T> &stack) {
    Stack<T> tempStack1;
    Stack<T> tempStack2;
    std::vector<T> vector1;
    std::vector<T> vector2;
    bool a = true;
    while(!stack.isEmpty()){
        if(stack.size() % 2 == 0){
            int n = stack.size() / 2;
            int count = 0;
            while(count < n){
                tempStack1.push(stack.pop());
                count++;
            }
            while(count < stack.size()){
                tempStack2.push(stack.pop());
                count++;
            }
            while(!tempStack1.isEmpty() || !tempStack2.isEmpty()){
                if(a && !tempStack1.isEmpty()){
                    stack.push(tempStack1.top());
                    tempStack1.pop()
                }
                else if(!a && !tempStack2.isEmpty()){
                    stack.push(tempStack2.top());
                    tempStack2.pop();
                }
                a = !a;
            }
        }
        if(stack.size() % 2 == 1){
            int n = stack.size /2;
            int count = 0;
            while(count < n){
                tempStack1.push(stack.pop());
                count++;
            }
            while(count < stack.size()){
                tempStack2.push(stack.pop());
                count++;
            }
            while(!tempStack1.isEmpty() || !tempStack2.isEmpty()){
                if(a && !tempStack1.isEmpty()){
                    stack.push(tempStack1.top());
                    tempStack1.pop()
                }
                else if(!a && !tempStack2.isEmpty()){
                    stack.push(tempStack2.top());
                    tempStack2.pop();
                }
                a = !a;
                while(!tempStack2.isEmpty()){
                    stack.push(tempStack2.top());
                    tempStack.pop();
                }
            }
        }
    }
}

// ============================================================================
// Question 4: Next Greater Element
// ============================================================================
template <typename T> std::vector<T> nextGreaterElement(Stack<T> stack) {

}

} // namespace StackUtils

#endif // STACK_QUESTIONS_NON_MEMBER_TPP
