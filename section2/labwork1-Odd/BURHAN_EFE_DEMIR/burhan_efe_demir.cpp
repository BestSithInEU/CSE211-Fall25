// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	
	template <typename T>
	bool isSorted(const LinkedList<T>&list){
		if (list.head == nullptr || list.head->next == nullptr){
			return true;
		}
		
		Node<T>* current = list.head;
		
		while (current->next != nullptr) {
			
			if (current->data > current->next->data){
				return false;
			}
			current = current ->next;
		}
	}

}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {

	template <typename T>
	LinkedList<T> splitInHalf(LinkedList<T> &list) {
		LinkedList<T> secondHalf;
		
		if (list.head. == nullptr || list.head->next ==nullptr) {
			
			return secondHalf;
		}
		
		size_t firstHalfSize = (list.count +1) / 2;
		size_t secondHalfSize = (list.count - firstHalfSize )
		
		Node<T>* current = list.head;
		for (size_t i = 1; i<firstHalfSize; i++) {
			current = current -> next;
		}
		secondHalf.head=current->next;
		secondHalf.count=secondHalfSize; 
		
		currnet->next = nullptr;
		list.count = firstHalfSize
		
		return secondHalf;
	}
	
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	
	

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
