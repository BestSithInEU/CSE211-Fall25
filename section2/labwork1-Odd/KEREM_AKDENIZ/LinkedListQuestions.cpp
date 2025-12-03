// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	Node<T>* cur = list.head;
	Node<T>* nextone = cur->next;

	while(nextone != nullptr){
		if(cur->data > nextone->data){
			return false;
		}
		cur = nextone;
		nextone = nextone->next;
	}
	return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	LinkedList<T> secHalf;
	if(list.head == nullptr) return secHalf;

	Node<T>* ptr1 =list.head;
	Node<T>* ptr2 = list.head;
	Node<T>* prev = nullptr;

	while(ptr2 != nullptr && ptr2->next != nullptr){
	ptr2 = ptr2->next->next;
	prev = ptr1;
	ptr1 =ptr1->next;
	}

	if(prev != nullptr){
	prev->next = nullptr;
	secHalf.head = ptr1;
	}
	return secHalf;
}
// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	node<T>* ptr1 = list.head;
	node<T>* ptr2 = list.head;

	for (size_t i = 0; i < n; i++){
	if (ptr1 == nullptr) return false;
	ptr1 = ptr1->next;
	}

	while(ptr1){
	ptr1 = ptr1->next;
	ptr2 = ptr2->next;
	}

	result -> ptr2->data;
	return true;

}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n){}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
