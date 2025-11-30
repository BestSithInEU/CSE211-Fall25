// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>


// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
    if(list.empty() == 1){
        return 0;
}
    int count = 0;
    Node<T>* cur = head;
    for(; cur != NULL;cur = cur->next){
        if(cur->data == value){
	    count++;
        }

    }
return count;

}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
    Node<T>* prev = head->next;
    Node<T>* cur = prev->next;
    Node<T>* nextt = cur->next;
    while(nextt != NULL){
        prev->next = nextt;
	cur->next = prev;
	
	prev = nextt->next;
	cur = prev->next;
	nextt=cur->next;
	
	}
    
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
    Node<T>* prev = head;
    Node<T>* curr = prev->next;
    for(;k>0;k--){
        prev=prev->next;
	curr = curr->next;
    }
    prev->next = NULL;
    Node<T>* newHead = curr;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = head;
    head = newHead;

   
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
