// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
  Node<T>* current = head; 
  while(current->next != nullptr){
  	if(*current == list[index]){
  		result = *current;
  		return result;
	  }
	  else{
	  	current = current->next;
}
  }
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  Node<T>* current = head; 
  while(current->next != nullptr){
  	if(current->data == target){
  		current->data = newValue;
  		return;
	  }else{
	  	current = current->next;
	  }
  }
  
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  Node<T>* current = head;
  while(current->next != nullptr){
  	if(current->next->data == value){
  		Node<T>* toDelete = current->next;
  		current->next = toDelete->next;
  		delete toDelete;
  		continue;
	  }else{
	  	current = current->next;
	  }
  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  if(head == nullptr || current->next == nullptr){
  	return;
  }
  int count=0;
  while(count<sizeof(list)){
  	head = current->next;
  }
}


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
