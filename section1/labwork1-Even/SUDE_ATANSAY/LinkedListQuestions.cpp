src/LinkedListQuestions.cpp
//#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>
#include <LinkedList.h>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  if (!list.head) return false;
  auto current = list.head;
  size_t i = 0;
 
  while (current) { 
     if (i == index) {
       result = current->data;
       return true;
     }
    current = current->next;
    i++;
   }
 return false; 
}


// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  auto current=list.head;
  while(current){
  	if(current->data == target){
	  current->data=newValue;
	  return true;
	  }
	  current=current->next;
	  }
	   return false;	
  }
  


// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  while(list.head && list.head->data == value){
  	auto temp = list.head;
    list.head = list.head->next;
    delete temp;
    list.size--;
   }
   auto current=list.head;
   while(current && current->next){
   if(current->next->data == value){
   	auto temp = current->next;
    current->next = current->next->next;
    delete temp;
    list.size--;
   }
   else{
   	current = current->next;
   }
   }
  }


// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
	Node<T>* prev = nullptr;
    Node<T>* current = list.head;
    Node<T>* next = nullptr;

    while (current) {
    	next=current->next;
    	current->next=prev;
    	prev=current;
    	current=next;
    }
    list.head=prev;
  
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);








