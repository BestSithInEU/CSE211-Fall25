// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	int count = 0;
	Node<T>* temp = list.head;
	while (temp)
	{
		if (temp->data == value)
			count++;
		temp = temp->next;
	}
	return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	if (!list.head)			return;
	if (!list.head->next)	return;
	Node<T>* prev = list.head;
	Node<T>* cur = list.head->next;
	Node<T>* next = list.head->next->next;
	list.head = cur;
	list.head->next = prev;
	prev->next = next;
	
	Node<T>* temp;
	
	prev = list.head->next;
	cur = prev->next;
	while (cur->next)
	{
		next = cur->next;
		prev->next = next;
		temp = next->next;
		next->next = cur;
		cur->next = temp;
		prev = cur;
		cur = prev->next;
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	if (k == 0) return;
	k = k % list.count;
	Node<T>* tail = list.head;
	Node<T>* prev;
	for (int i = 0; i < k; i++)
	{
		tail = list.head;
		while (tail->next)
		{
			prev = tail;
			tail = tail->next;
		}
		tail->next = list.head;
		prev->next = NULL;
		list.head = tail;
	}
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	Node<T>* prev = list.head;
	Node<T>* cur = prev->next;
	Node<T>* next;
	Node<T>* temp;
	int index;
	int change_count = 1;
	if (prev->data > pivot)
	{
		next = cur->next;
		list.head = cur;
		list.head->next = prev;
		prev->next = next;
	}
	while (change_count != 0)
	{
		change_count = 0;
		prev = list.head;
		cur = prev->next;
		while (cur->next)
		{
			next = cur->next;
			if (cur->data >= pivot) // Swap if the value on the left is greater then the value on the right. (Like bubble sort)
			{
				prev->next = next;
				temp = next->next;
				next->next = cur;
				cur->next = temp;
				change_count++;
				prev = next;
			}
		}
		break; // To be able to test. Otherwise gets into infinite loop because of logic error
	}
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
