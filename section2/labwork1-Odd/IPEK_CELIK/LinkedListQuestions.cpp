// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	LinkedList<T>* llist = list
	if(list.empty() == 1) return 1;
	if(llist->next == NULL) return 1;
	
	int prev = llist->data;
	llist = llist->next;
	while(llist != NULL){
		if(llist->data < prev){
			return 0;
		} else{
			prev = llist->data;
			list = llist->next;
		}
	}
	return 1;
}


// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	int lenght = 0;
	LinkedList<T>* temp = list;
	while(temp != NULL){
		lenght++;
		temp = temp->next;
	}
	
	temp = list;
	int position;
	if(lenght % 2 == 0){
		position = lenght / 2 - 1;
	} else{
		position = lenght / 2;
	}
	
	for(int i = 0; i < position; i++){
		temp = temp->next;
	}
	
	LinkedList<T>* secondhalf = temp->next;
	temp->next = NULL;
	
	return secondhalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	int lenght = 0;
	if(n > lenght) return 0;
	if(list == NULL) return 0;
	
	LinkedList<T>* temp = list;
	while(temp != NULL){
		lenght++;
		temp = temp->next;
	}
	temp = list;
	
	int position = lenght - n + 1; 
	for(int i = 0; i < position; i++){
		temp = temp->next;
	}
	return temp->data;
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
