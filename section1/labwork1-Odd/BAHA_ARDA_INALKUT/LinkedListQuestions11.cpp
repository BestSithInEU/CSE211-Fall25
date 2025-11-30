// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	
LinkedList<T>::LinkedList( list ) : head(nullptr), count(0) {

while (LinkedList( nullptr ) != Null ){
	
}



Node<T>* current = head;
  while (current->next != nullptr) {
    
	
	
	 if (current->next == new Node<T>(value))
     count++;
     current = current->next;
  }

}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
