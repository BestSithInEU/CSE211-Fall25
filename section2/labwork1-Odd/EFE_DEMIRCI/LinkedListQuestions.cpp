// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	if (list.empty()||list.size()==1){
		
		return true;
	}
	
	
	Node<T>* cur=list.head;
	
	while(cur->next!=nullptr){
		if(cur->data > cur->next->data){
			
			return false;
		}
		cur=cur->next;
		
		
	}
	
	return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	
	LinkedList<T> secondHalf;
	
	size_t value=list.size()/2;//5/2=2     1 2 3 4 5 6  
	Node<T>* cur=list.head;
	
	if(list.size()%2==1){
		for(size_t i=0;i<value;i++){
			cur=cur->next;
	}
		secondHalf.head=cur->next;
		cur->next=nullptr;
	}
	
	else{
		for(size_t i=0;i<(value-1);i++){
			cur=cur->next;
	}
		secondHalf.head=cur->next;
		cur->next=nullptr;
	}
		
		
	
	
	secondHalf.count=value;
	list.count=value+1;
	
	return secondHalf;
	
	
	
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	
	if((n==0)||(n>list.size())){
		
		return false;
	}
	
	Node<T>* cur=list.head;
	Node<T>* prev=list.head;
	
	for(size_t i=0;i<n;i++){
		cur=cur->next;
	}
	
	while (cur!=nullptr){
		cur=cur->next;
		prev=prev->next;
	}
	result = prev->data;
	
	return true;
	
	
	
}

// Q4: Delete every Nth node
template <typename T> void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	
	Node<T> lesser(0);
	Node<T> bigger(0);
	
	Node<T>* taillesser = &lesser;
	Node<T>* tailbigger = &bigger;
	
	Node<T>* cur = list.head;
	
	while(cur!=nullptr){
		
		if(cur->data < pivot){
			taillesser->next=cur;
			taillesser=taillesser->next;
		}
		else{
			tailbigger->next=cur;
			tailbigger=tailbigger->next;
		}
		cur=cur->next;
		
	}
	
	list.head=lesser.next;
	taillesser->next=bigger.next;
	tailbigger->next=nullptr;
	
	
	
	
	
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void  partitionAroundValue(LinkedList<int> &, const int &);
