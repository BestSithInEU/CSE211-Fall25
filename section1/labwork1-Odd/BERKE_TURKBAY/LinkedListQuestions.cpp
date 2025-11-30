// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>
using namespace std;
// Q1: Count occurrences of a value
template <typename  T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	int count;
	Node<T>* temp=list;
	while(temp->next!=nullptr){
		if(temp->data==value){
			count++;
		}
		temp=temp->next;
	}

}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* temp=list;
	Node<T>* changer=list;
	while(temp->next!=nullptr){
		if(temp->next->next!=nullptr){
			changer->next->next=temp;
			temp->next=changer->next->next;
		
		}
	}
}

// Q3: Rotate list to the right by k positions
template <typename  T>
void rotateRight(LinkedList<T>& list, size_t k) {
	int size=0;
	Node<T>* temp=list;
	while(temp->next!=nullptr){
		size++;
		temp=temp->next;
	}
	int number=size-k;
	Node<T>* newhead=list;
	for(int i=0;number!=k;i++){
		newhead=newhead->next;
	}
	Node<T>* newtail=list;
	for(int i=1;number!=k;i++){
		newhead=newhead->next;
	}
	temp->next=list;
	newtail->next=nullptr;
	
}

// Q4: Partition around a value
template <typename  T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	Node<T>* temp=list;
	Node<T>* newhead=list;
	while(temp->next!=nullptr){
		if((temp->data)<5){
		newhead=temp;
		break;
		}
		temp=temp->next;	
	}
	while(temp->next!=nullptr){
		if((temp->data)<5){
			newhead->next=temp;
			newhead=newhead->next;
		}
	}
	Node<T>* temp1=list;
	while(tem1p->next!=nullptr){
		if((temp1->data)>=5){
			newhead->next=temp1;
			newhead=newhead->next;
		}
	}
	newhead->next=nullptr;
											
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
