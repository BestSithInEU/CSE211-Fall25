// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
    size_t count = 0;

    while (curr != nullptr) {  
        if (curr->data == value) {
            count++; 
		}
        curr = curr->next; 
    }
    return count; 
}


// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	if(head == nullptr){
		return;
	}
	Node *current = head;
	Ndoe *prev = nullptr;
	Node *new = nullptr;
	while(current){
		Node *groupPrev = nullptr;
		Node *groupCurrent = current;
		Node *groupNext = nullptr;
	}
	while(groupCurrent != nullptr){
		groupNext = groupCurr ->next;
		groupCurr ->next = groupPrev;
		groupPrev = groupNext;
	}
	prev =curent;
	current=groupCurrent;
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	if(head == nullptr){
		return;
	}

	Node* prev = nullptr;
    Node* curr = head;
    head = head->next;

    while (curr && curr->next) {
        Node* first = curr;
        Node* second = curr->next;

        first->next = second->next;
        second->next = first;

        if (prev){
            prev->next = second;
		}
		
        prev = first;
        curr = first->next;
    }
}
	


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
