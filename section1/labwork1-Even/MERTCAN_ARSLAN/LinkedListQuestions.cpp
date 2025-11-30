// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
   if (index<list.size()){
   	return false;
   }else{
   		Node<T>* current = list.head;
   		while(current != nullptr) {
   		current = current->next;
 		result = current.value;
 		delete current;
 		
   }
   return true;
}
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	Node<T>* current = list.head;
   for (int i = 0; i < list.size(); i++){
   	
   		if (current.value == target){
   			current.value = newValue;
   			return true;
		   }else{
		   	current = current-> next;
		   }
   }
   delete current;
   return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  	Node<T>* current = list.head;
  	Node<T>* temp = nullptr;
  	Node<T>* headnode = list.head;
  	while(current != nullptr){
  		// for checking and changing head
  		if (headnode.value == value){
  			headnode = headnode->next;
  			list.head = headnode;
  			current = headnode;
		  }else {
		  	temp = current;
		  	current = current->next;
		  	if (current.value == value){
		  		temp->next = current->next;
		  		current = current->next;
		  		
			  }
		  }
		  	
		  
	  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
	Node<T>* prev = list.head;
	Node<T>* current = list.head;
	Node<T>* next = list.head;
	current = current->next;
	next = current->next;
	current->next = prev;
	prev->next = nullptr;
	prev = current;
	while(current != nullptr){
		current = next;
		next = current->next;
		current->next= prev;
		prev = current;
	}
	list.head = current;
	
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
