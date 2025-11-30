// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
	
	auto current = list.head;
	
	size_t i = 0;
	
	while (current != nullptr && i < index) {
		current = current->next;
		i++;
	}
	if ( i == index ){
		result = current->data;
		return 1;
	}
	return 0;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	
	if (list.head == nullptr){
  		return 0;
 	 }
  
  	auto current = list.head;
  
  	while (current != nullptr){
  		if(current->data == target){
  			current->data = newValue;
  			return 1;
	  	}
		current = current->next;
  	}
  	return 0;
}


// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
	auto current = list.head;
	size_t i = 0;
	
	while(current != nullptr){
		if(current->data == value){
			current = current->next;
			list.erase(i);
			continue;
		}
		current = current->next;
		i++;
	}
	
	
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
	auto current = list.head;
	auto last = current->next;
	int perv = current->data;
	
	while(current != nullptr){

		while((last!= nullptr)  || (last->next->data != perv)) {
			last = last->next;
		}
		
		int perv = current->data;
		current->data = last->data;
		last->data = perv;
		
		current = current->next;
		last = current->next;
	}
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
