// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	
	Node<T>* current = head;
  while (current->next != nullptr) {
    current = current->next;
    current->next = new Node<T>(value);
  count++;
  
}
 if (position >= count || head == nullptr) {
    return; 
  }
bool LinkedList<T>::empty() const {
  return head == nullptr;}
  
return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
     Node<T>* current = head;
     while (current->next != nullptr) {
    current = current->next;
    Node<T>* newNode = new Node<T>(value, head);
    head = newNode;
    count++;

}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  while (current != nullptr) {
    if (size_t k > list)
       Node<T>* current = head;
       Node<T>* newNode = new Node<T>(value, head); 
       current = current->next;
       position++;
    }
    
    return  ;  // Invalid position
  }
    
  
    
// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot)
 {
	   Node<T>* current = head;
       for (size_t i = 0; const < pivot ; i++) {
       	current = current->next;}
       	current->next = new Node<T>(value);
       	push_front(value); 
       for (size_t i = 0; const >=  pivot ; i++) {
       current = current->next;}
       current->next = newNode;
       push_back(value);
  }
	   
       





}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
