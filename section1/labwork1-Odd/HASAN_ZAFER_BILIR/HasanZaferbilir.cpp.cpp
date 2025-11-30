// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {

	int count = 0;
	Node<T>* current = head;
		
	while (current->next != nullptr){
  		if (current->data == value){
  			count++;
		  }
		  current  = current->next
  	}
  	return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	Node<T>* Next = head ;
	Node<T>* current = head;
	Node<T>* temp = head;
	
	Next = current -> next; 
	
	while (Next -> next != nullptr){
		
		temp->next = Next->next;
		Next->next = current->next;
		current->next = temp->next;
		
		Next = Next->next ;	
	}
	
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	
	Node<T>* Next = head;
	Node<T>* current = head;
	Node<T>* temp = head;
	
	Next = current -> next ;
	
	while(Next-> next != nullptr){
		
	}

}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	
	Node<T>* Next = head;
	Node<T>* current = head;
	
	while(current->next != nullptr){
		if (current->data >= pivot){
			Node<T>* newNode = new Node<T>(data, head);
			newNode->data = current->data;
			newNode ->next = current->next;  
		}
		current = current -> next ;
	}
	


}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
