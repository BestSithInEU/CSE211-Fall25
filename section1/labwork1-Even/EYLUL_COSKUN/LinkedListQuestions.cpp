// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here

  Node<T>* current = list.head;
  int position = 0;
  
  while (current != nullptr) {
  	if (position != index) {
  		position++;
	  } else {
	  	current->data = result;
	  	break;
	  }
  }
  return result;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  
  Node<T>* current = list.head;
  
  while (current != nullptr) {
  	if (current->data == target) {
  	    current->data = newValue;
  	    return true;
    } else {
  		current = current->next;
    }
  }
  return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  
  Node<T>* current = list.head;
  
  for (size_t i = 0; i < position - 1; i++) {
    current = current->next;
  }
  
  while (current != nullptr) {
  	if (current->data == value) {
  		Node<T>* toDelete = current->next;
  		current->next = toDelete->next;
  		delete toDelete;
  		current = current->next;
	  } 
  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  
  Node<T>* prev = nullptr;
  Node<T>* current = list.head;
  Node<T>* next = current->next;
    
    
    
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
