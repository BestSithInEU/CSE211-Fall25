#ifndef STACK_QUESTIONS_MEMBER_H
#define STACK_QUESTIONS_MEMBER_H

#include "Stack.hpp"
#include <algorithm>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>
using namesapace std;

template <typename T> class Stack; // Forward declaration


// Extend Stack with additional member functions
template <typename T> class StackQuestions : public Stack<T> {
public:
  using Stack<T>::Stack; // Inherit constructors


  T findMiddle(Stack s) const{
  	
  	if (this->isEmpty()) { 
        throw std::underflow_error("Stack is empty");

    }

    Stack<T> copy = *this; 



    std::vector<T> elems;

    while (!copy.isEmpty()) {
        elems.push_back(copy.top());
        copy.pop();

    }



    size_t n = elems.size();
    size_t idx = n / 2;
    return elems[idx];

}

void StackQuestions<T>::insertAtBottom(Stack<T>& st, const T& value) {

    if (st.isEmpty()) {
        st.push(value);
        return;

    }

    T topv = st.top();
    st.pop();
    insertAtBottom(st, value);
    st.push(topv);

}



  void reverse(){
  	  if (this->isEmpty()) return;
    T topv = this->top();
    this->pop();
    reverse();
    insertAtBottom(*this, topv);
  }
  
  
};

// Include template implementation
#include "StackQuestionsMember.tpp"

#endif // STACK_QUESTIONS_MEMBER_H
