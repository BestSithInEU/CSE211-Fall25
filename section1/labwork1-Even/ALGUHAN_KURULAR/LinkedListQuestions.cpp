// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  Node<T>* current = list.head;
  
  if(index > list.size()){
  	return -1;
  }
  for (int i=0; i < index;i++){
  	if(current->next != nullptr){
  		result = current->next->next->data;
  		return true;
	  }
	else
		return false;  
  }
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  Node<T>* current = list.head;
  while (current){
  	if (current-> data == target){
  		current->data = newValue;
  		return true;
	  }
	else
		current = current->next;
  }
  return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  Node<T>* current = list.head;
  Node<T>* prev = nullptr;
  Node<T>* lastNode = list.head ;
  
  
  while (current){
  	Node<T>* temp = nullptr;
  	if(current->data == value){
  		if(list.head == current){
  			list.head = current->next;	
		}
		else{
			
			prev->next = prev->next->next;
			temp = current;
			temp->next = nullptr;
  			delete temp;
  			
		}
			 		
  		
	  }
	else
	 	prev = current;
	 	current = current->next; 
  }
  
  
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  Node<T>* prev = nullptr;
  Node<T>* current = list.head;
  Node<T>* next = nullptr;
  
  while(current != nullptr){
  	next = current->next;
  	current->next = prev;
  	prev = current;
  	current = next;
  	
  }
  list.head = prev;
  
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
