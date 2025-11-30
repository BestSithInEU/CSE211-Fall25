// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
	Node<T>* start = list.head;
	int count = 0;
	while (count < (int)index) {
		start = start->next;
		count++;
	}
	int x = start->data;
	if (x == result) {
		return true;
	}
	else {
		return false;
	}
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	Node<T>* start = list.head;
	while (start) {
		if ((start->data) == target) {
			(start->data) = newValue;
			return true;
		}
		start = start->next;
	}
	return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
	Node<T>* start = list.head;
	while (start) {
		if ((start->data) == value) {
			Node<T>* toDelete = start->next;
            start->next = toDelete->next;
            delete toDelete;
		}
		start = start->next;
	}
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  	Node<T>* start = list.head;
	int count = 1;
	while (start->next) {
		start = start->next;
		count++;
	}
	if (count == 1) {
		return;
	}
	for (int i = 0; i < count / 2; i++) {
		Node<T>* first = list.head;
		int j = 0;
		while (j < i) {
			first = first->next;
			j++;
		}
		Node<T>* second = list.head;
		int k = 0;
		while (k < (count - 1 - i)) {
			second = second->next;
			k++;
		}
		const T temp = first->data;
		first->data = second->data;
		second->data = temp;
	}
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
