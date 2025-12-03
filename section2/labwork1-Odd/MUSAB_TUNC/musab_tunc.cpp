// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	Node* temp = list.head;
	while (temp->next!= NULL)
	{
		if (temp > temp->next){
		return 0;
		}
		temp= temp->next;
	}
	
	return 1;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	Node* temp = list.head;
	int count;
	
	while(temp!=NULL){
		count += 1;
		temp= temp->next;
	}
	
	if (count % 2 == 0){
		int var = count /2 ;
		Node* temp2= list.head;
		for(int i=0; i !=var; i++){
			temp2= temp2->next;
		}
		
		Node* head2 = new Node();
		head2 = temp2 -> next;
		temp2->next = NULL;
		return head2;
		 
	}
	else{
		int var = count /2 ;
		Node* temp2= list.head;
		for(int i=0; i !=var+1; i++){
			temp2= temp2->next;
		}
		
		Node* head2 = new Node();
		head2 = temp2 -> next;
		temp2->next = NULL;
		return head2;
		
	}
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
