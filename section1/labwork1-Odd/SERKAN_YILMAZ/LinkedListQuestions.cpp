// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>


// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
		  	Node<T>* newNode = new Node<T>(value, head);
  			head = newNode;
 			count++;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T> current = list.head;
	while(current != NULL && current->next !== NULL){
		swap(current -> data, current -> next ->data);
		current = current ->next->next;
	}
	}

}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {

}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {

}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
