// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	size_t count = 0;
	Node<T>* cur = list.head;
	while( cur != nullptr){
		if(cur -> data == value )count++;
		cur = cur->next;
	}
	return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* prev = list.head; 
	Node<T>* cur = prev -> next;
	
	while(cur != nullptr){
		if(cur -> data == prev -> data + 1 ){
			Node<T>* temp = prev;
			prev -> data = cur -> data;
			cur -> data =  temp -> data;
		}
		prev = prev -> next;
		cur = cur -> next;
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	 
	for(int i = 0;i<k;i++){
			Node<T>* cur = list.head -> next;
			Node<T>* prev = list.head;
			
		while(cur -> next != nullptr){
			Node<T>* temp =  cur;
			cur -> next -> data = temp -> data;
			cur = cur -> next;
			
		}
	}
	
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	Node<T>* cur = list.head;
	Node<T>* cur1 = list.head;
	
	Node<T>* before = list.head;
	Node<T>* after = list.head;

	Node<T>* bcur = before;
	Node<T>* acur = after;
	int count = 0;
	
	while(cur != nullptr){
		if(cur -> data < pivot){
			before -> data =  cur -> data;
			before =  before -> next;
			count++;
			
		}else{
			after -> data = cur -> data;
			after = after -> next;
		}
		cur = cur -> next;
	}
	
	
	int i = 0;
	do{
		cur1 -> data = bcur -> data;
		bcur = bcur -> next;
		cur1 = cur1 -> next;
		i++;
	}
	while(i<count);
	
	while(cur1 != nullptr){
		cur1 -> data = acur -> data;
		acur = acur -> next;
		cur1 = cur1 -> next;
	}

}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
