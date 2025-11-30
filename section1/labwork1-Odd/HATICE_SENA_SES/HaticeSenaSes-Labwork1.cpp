// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	int count = 0;
	
	
	if(node == nullptr) {
		return;
	}
	Node<T>* current = head;
  	while (current->next != nullptr) {
    current = current->next;
    
    if(current->data == value){
    	count++;
    }
	return count;


}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	if(head || head-> == nullptr) {
		return;
	}
	Node* temp = head->next;
	head->next = temp->next;
	temp->next = head;
	head = temp;
	
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	if(k==0 || head==0){
		return;
	}
	node* temp = head;
	for(int i = 0; i <= length, i++){
		temp = temp->next
		
	}

}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
	Node<T>* current = head;
  	while (current->next != nullptr) {
    current = current->next;
    
    if(current->data <= pivot){
    	cout<< current->data;
	}
	cout<< current->data;
	
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
