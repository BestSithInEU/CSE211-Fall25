// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
int temp;	
int count = 0;
Node<T>* list = head;
  while (list->next != nullptr) {
    current = list->next;
	temp = list.value;
	if(temp == value){
	count++;
	}	
}
return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
list
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
for(i=k;i=0;i--){
	
// Traverse to last node
  list* current = head;
  while (current->next != nullptr) {
    current = current->next; 
		}
// Insert at front - O(1)
Node<T>* newNode = current
	head = newNode;
		}
	delete current;						
	}
}

// Q4: Partition around a value (tüm listeyi gez. karsilastirma yap ona göre diz)
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
