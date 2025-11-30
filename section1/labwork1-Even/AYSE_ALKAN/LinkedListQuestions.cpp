// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
  Node<T>* current = list.head;
  size_t counter=0;
  
  while (current != nullptr){
  if (count==index){
  result= current-> data ;
  return true;
}
current = current-> next ;
count ++;
  }
  return false ;}
  

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  // TODO: Implement your solution here
  
  Node<T>* current = list.head;
  
   while (current != nullptr){
  if (current-> data == target){
  current-> data = newvalue ; 
  return true;
}
current = current-> next ;

  }
  return false ;}
  
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
while (list.head != nullptr) && (list.head->data == value) {
Node<T>* temp = list.head;
list.head = list.head->next;
delete temp;
}

Node<T>* current = list.head;

while (current != nullptr && current->next != nullptr) {
if (current->next->data == value) {
Node<T>* temp = current->next;
current->next = current->next->next;
delete temp;
} else {
current = current->next;
}
}
}


// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  while (current != nullptr) {
  	Node<T>* prev = nullptr;
Node<T>* current = list.head;
Node
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
