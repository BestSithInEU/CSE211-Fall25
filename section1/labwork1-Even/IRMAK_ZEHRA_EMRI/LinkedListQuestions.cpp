// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
  
  Node<T>*curr=list.head;
  int position=0;

  if(curr==nullptr || curr->next==nullptr){
  	return false;
  }
  while(curr!=nullptr){
  	if(curr->data==value){
  		return position;
  		curr=position;
  		for(size_t i=0;i<position-1;i++){
  			result=curr->data;
		  }
	  }
	  curr=curr->next;
	  position++;
  }
  return -1;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  if(curr==nullptr || curr->next==nullptr){
  	return false;
}
Node<T>*curr=list.head;
while(curr!=nullptr){
	if(curr->data==target){
		curr->data=newValue;
	}
	curr=curr->next;
}
return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  size=list.length;
  Node<T>*temp=list.head;
  Node<T>*curr=list.head;
  
  while(curr!=nullptr){
  	if(curr->data==value){
  		  curr=temp;
  		  curr=curr->next;
		  delete temp;
	  }
	  size--;
	  curr=curr->next;
  }
  deleteAllOccurences();
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  
  Node<T>*prev=&temp;
  Node<T>*curr=list.head;
  Node<T>*next=curr->next;
  
  
  while(curr!=nullptr){
  	prev->next=curr;
  	next->next=nullptr;
  	next->next=curr;
  	next=list.head;
  	curr=curr->next;

  }
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
