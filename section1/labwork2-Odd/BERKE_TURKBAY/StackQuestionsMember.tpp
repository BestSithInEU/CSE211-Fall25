#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: getKthFromTop
// ============================================================================
template <typename T> bool StackQuestions<T>::getKthFromTop(size_t k,int&x) const {
  // TODO: IMPLEMENTATION
    Stack<int> tempStack;
    if(k>size())
        cout<<"overflow"<<endl;
        return false;
    Node* temp=topNode;
    for(int i=0;i<k;i++){
        temp=temp->next;
    }
    cout<<"output ="<<temp->item<<endl;
    x=temp->item;
    return true;
}

// ============================================================================
// Question 2: sortStack
// ============================================================================
template <typename T> void StackQuestions<T>::sortStack() {
  // TODO: IMPLEMENTATION
    Stack<int> s1Temp;
    int size=size();
    while(topNode!=nullptr){
        Node* temp=topNead;
        int min_index=1;
        for(int i=1;i<size;i++){
            if(topNode->item>temp->item)
                min_index=i;
            temp=temp->next;
        }
        s1Temp.push(temp);
        pop(temp);
    }
    int counter=0;
    while(size>counter){
        push(s1Temp.topNode));
        s1.pop();
        counter++;
    }
}

#endif // STACK_QUESTIONS_MEMBER_TPP
