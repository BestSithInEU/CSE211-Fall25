// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
Node<T>* temp=list;
int count=0;
if(list->next==nullptr){
	return 0;
}
while(temp->next!=nullptr){
	if(temp->data==value){
		count++;
	}
	temp=temp->next;
}
return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* current=list->next;
	Node<T>* prev=list;
	Node<T>* next_p=list->next->next;
	Node<T>* temp=nullptr;
	
	while(next_p->next!=nullptr){
		if(prev==list){
			current->next=prev->next;
			prev->next=next_p;
			list=current;//head gÃ¼ncellendi
			//swap between prev and current
			temp=current;
			current=prev;
			prev=temp;
		}
		if(prev!=list){
			current->next=prev->next;
			prev->next=next_p;
			temp=current;
			current=prev;
			prev=temp;
		}
		temp=nullptr;//safety
		next_p=next_p->next;
		current=current->next;
		prev=prev->next;
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
for (int i=0;i<size_t;i++){

	Node<T>* current = list;
	Node<T>* temp = list;
	while (current->next->next != nullptr) {
	    current = current->next;
	  }
	  temp=current->next;
	  temp->next=list;
	  current=nullptr;
	  list=temp;
	  temp=nullptr;
}
  
  
  
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	LinkedList<int> copy_list;	
	Node<T>* current = list;
	
	while(current->next!=nullptr){
	
		if(current->data < pivot){
			copy_list.push_back(current->data);
			current=current->next;
				
				
		}
	}
	current=list;
	while(current->next!=nullptr){
		
		if(current->data >= pivot){
			copy_list.push_back(current->data);
			current=current->next;
	
	}
	list=copy_list;
	
}

	728316
	278316
	273816
	273186
	
	237186
	231786
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
