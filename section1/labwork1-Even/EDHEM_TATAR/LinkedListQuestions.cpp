// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
  if(index < 0 || index > list.size()){
  	return false;
  }
  Node<T> *cur = list.head;
  
  for(int i = 0; i < index; i++){
  	cur = cur -> next;
  }
  
  result = cur -> data;
  return true;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  Node<T> *cur = list.head;
  
  int found = 0;
  
  while(cur != NULL){
  	if(cur -> data == target){
  		cur -> data = newValue;
  		found = 1;
  		break;
	  }
	cur = cur -> next;
  }
  
  if(found)
  	return true;
else
	return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  Node<T> *cur = list.head;
  int i = 0;
  
  while(cur != NULL){
  	if(cur -> data == value && i == 0){
  		Node<T> *temp = cur;
  		cur = cur -> next;
  		list.head = cur;
  		temp -> next = NULL;
  		delete temp;
  		temp = NULL;
  		i++;
	  }
	  else if(cur -> data == value && i != 0){
	  	Node<T> *prev = list.head;
	  	for(int j = 0; j < i - 1; j++){
	  		prev = prev -> next;
		  }
	  	Node<T> *temp = cur;
	  	cur = cur -> next;
	  	prev -> next = cur;
	  	temp -> next = NULL;
	  	delete temp;
	  	temp = NULL;
	  	i++;
	  }
	  else{
	  	i++;
	  	cur = cur -> next;
	  }
  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  if(list.empty() || list.head -> next == NULL)
  	return;
  	
  	Node<T> *cur = list.head;
  	Node<T> *prev = NULL;
  	Node<T> *next = cur -> next;
  	
	
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
