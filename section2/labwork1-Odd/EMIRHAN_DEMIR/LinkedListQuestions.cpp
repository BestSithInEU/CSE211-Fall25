// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	if(head == nullptr || head->next nullptr ){
		return true;
	}
	
	Node<T>current* = head;
	
	while(curren->next != nullptr){
		if(current->data < current->next->data){
			return true;
		}
		else return false;
	}
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	LinkedList<int> list1;
	Node<T>current* = head;
	if((list.size()%2)==0){
		for(int i=0 ; i<(size/2)+1 ; i++ ){
			current = current->next;
		}
		for(int i=0 ; i<(size/2) ; i++){
			list1.push_back(current->data)
			current = current->next;
			list.erase((size/2)+i);
		}
	}
	else{
		for(int i=0 ; i<(size/2)+2 ; i++ ){
			current = current->next;
		}
		for(int i=0 ; i<(size/2) ; i++){
			list1.push_back(current->data)
			current = current->next;
			list.erase((size/2)+i);
		}
		
		
		return list1.head;  
		
	}
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	if(head == nullptr || head->next nullptr ){
		return false;
	}
	
	Node<T>head* = x;
	Node<T>head* = y;
	
	for(int i=0 ; i<n ; i++){
		if(x->data == nullptr){
			return false;
		}
		x = x->next;
	}
	
	for(int i=0 ; i <list.size() ; i++){
		if(x->data == nullptr){
			result = y;
			return true;
		}
		else {
			x = x->next;
			y = y->next;
		}
	}

}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
