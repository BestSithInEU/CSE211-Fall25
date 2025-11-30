// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
        if(index < 0 || index >= list.size()) {
		return nullptr;
	}
        Node* temp = head;
        for(int i = 0; i < index; i++){
            temp = temp->next;
        }
        return temp;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  Node* temp = head;
  while (temp != nullptr){
  	if(temp -> value == target){
  		temp -> value = newValue;
  		return true;
	  }
	  temp = temp->next;
  }
  return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  Node* current = head;
        while(current != nullptr){
            Node* end = current;
            while(end -> next != nullptr){
                if( end -> next -> value == current -> value){ 
                    Node* temp = end -> next;
                    end -> next = end->next->next;
                    delete temp;
                } 
				else {
                    end = end->next;
                }
            }
            current = current->next;
        }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  Node* temp = head;
  head = tail;
  tail = nullptr;
  Node* end = temp -> next;
  Node* begin = nullptr;
  for(int i = 0; i < list.size(); i++){
  	end = temp-> next;
  	temp -> next = begin;
  	begin = temp;
  	temp = end;
  }
}
  
  
  
  
  
  

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
