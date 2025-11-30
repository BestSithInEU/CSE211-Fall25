// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
	T position;
	T count = 1;
	std::cout << "please choose the location so that we can get you that locations value:";
	std::cin>> position;
	Node<T> current = head;
	Node<T>* value = head;
	result = value;

    while (current != nullptr) {
    	if (count == position) {
      		result = value;
    	}
    	else{
    		count ++;
    		value = value->next;
		}
    }
	return result;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	*target = *newValue;
	
	if (replaceFirst(list, target, newValue)) {
8   	return 1;
9	}
	else{
  		return 0;
	}
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  Node<T>* current = head;
  int position = 0;

  while (current != nullptr) {
    if (current->data == value) {
    	Node<T>* temp = head;
        delete temp;
    }
    current = current->next;
    position++;
  }

  return -1;  // Not found
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
	T count = 0;
	Node<T>* temp = head;
	Node<T>* current = head;

    while (temp != nullptr) {
    	count++;
	}
	for(T i = 0;i <= count; i++){
		
	}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
