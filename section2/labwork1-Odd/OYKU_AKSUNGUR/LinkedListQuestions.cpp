// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	Node *current = head;
	
	if(current->next == nullptr){
		return true;// list is empty so i accepted that the list is sorted.
	}
	while(current->next!= nullptr){
		if(current < current->next){//ascending order.
			return true;
			
			
		}
		else 
			return false;
			
		current = current->next;
	}




}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	
	Node* slow = head;
	Node* current= head;
	Node* fast = head;
	
	while( fast->next != nullptr && fast->next->next!= nullptr){
		slow= slow->next;
		fast=fast->next->next;
	}
	LinkedList<int> secondHalf = splitInHalf(list);
	Node* secondHalfHead = slow->next;
	Node* current2= secondHalfHead;
	int size=0;
	
	
	while(current2 != nullptr){
		for(int i=0;i<size_t/2;i++){
			 secondHalf[i] = list[ size_t/2 +i];
		
			size++;//the size of the second list ;
		}
	}
	
		
		
	}
		
	


// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	
	if(n<0 || n>size_t){
		return false;//invalid case;
	}
	
	Node* current= head;
	Node* p= current->next;
	for(int i=0; i<size_t-n;i++){
		current= current->next;
		p=p->next;
		
	}
	
	return current;
	
	
	
	
		


}

// Q4: Delete every Nth node
 template <typename T>
 void partitionAroundValue(LinkedList<T>& list, const T& pivot){
 	Node* current =head;
 	
 	while(current->next != nullptr){
 		if(current->data<pivot){
 			current->next = pivot;
		 }
		 else if( current->data > pivot){
		 	pivot->next = current;
		 	
		 }
		 current = current->next;
	 }
 }
 		
 





}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
