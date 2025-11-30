// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	LinkedList<T>::LinkedList() : head(nullptr), count(0){}	
}
void LinkList<T>::push_front(const T& value){
	Node<T>*neewNode = new Node<T>(value,head);
	head = newNode;
	count++;
}














// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	 Node<T>* current = head;
  while (current->next != nullptr) {
    current = current->next;
  }














}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	Node<T>* current = head;
  for (size_t i = 0; i < position - 1; i++) {
    current = current->next;

	








}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) 
{
  Node<T>* current = other.head;
  while (current != nullptr) {
    push_back(current->data);
    current = current->next;
  }
}




}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);




