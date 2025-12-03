// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) 
{
	if(list.head==nullptr || list.head->next==nullptr){
		return true;
	}
	
	Node<T> * curr = list.head;
	while(curr->next!=nullptr){
		if(curr->data > curr->next->data)
			return false;
		curr = curr->next;
	}
	return true;
	
}


// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	
	Linkedlist<T> secondHalf;
	
	if(list.head==nullptr || list.head->next==nullptr)
		return secondHalf;	
}


// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
}



// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {

	if(n<=1){
		while(list.head!=nullptr){
			Node<T> *tmp = list.head;
			list.head = list.head->next;
			delete tmp;
		}
		return;
	}
	size_t count =1;
	Node<T> *curr = list.head;
	Node<T> *prev = nullptr;
	
	while(curr!=nullptr){
		if(count==n){
			prev->next = curr->next;
			delete curr;
			curr = prev->next;
			count=1;
		}else{
			prev=curr;
			curr=curr->next;
			count++;
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



