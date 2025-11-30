// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
	Node<T>* new_head=list.head;
	if(!list.empty()&&index<list.size()){
	
  for(size_t i=0;i<index;i++){
  	new_head=new_head->next;
  }
  result=new_head->data;
  return true;
}
else{
	return false;
}
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	Node<T>* new_head=list.head;
  if(!list.empty()){
  	while(new_head->data!=target){
  		new_head=new_head->next;
  		
  		
  		
	}
	new_head->data=newValue;
  	return true;
  }
  	//list is empty or value not found
  	return false;
  
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
	Node<T>* head=list.head;
	Node<T>* prev=list.head;
  while(head!=nullptr){
  	if(head->data==value){
  		if(head==list.head){
  		Node<T>* temp=head;
  		list.head=head->next;
  		head=list.head;
  		prev=head;
  		delete temp;
		  }
		else{
		
  		Node<T>* temp=head;
  		prev->next=head->next;
  		head=head->next;
  		delete temp;}
  		
	  }
	else{
		prev=head;
		head=head->next;
	}
	
  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  Node<T>* prev=list.head;
  Node<T>* cur=prev->next;
  Node<T>* nex=cur->next;
  
  while(nex!=nullptr){
  cur->next=prev;
  prev=cur;
  cur=nex;
  nex=nex->next;
}
cur->next=prev;
list.head->next=nullptr;
list.head=cur;

}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
