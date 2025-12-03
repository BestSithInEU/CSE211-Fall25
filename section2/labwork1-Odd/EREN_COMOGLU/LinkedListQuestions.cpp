// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	Node<T> *prev = nullptr;
	Node<T> *cur = list.head;
	if(list.head == nullptr){
		return false; //list is empty
	}
	while(list.head != nullptr && cur != nullptr ){
		prev = cur;
		cur = cur->next; 
		if(prev ->data > cur ->data){
			return false;
		}
	if(cur == nullptr){
		return true;
	}
	}
	

}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	LinkedList<T> temp;
	int count = 0;
	Node<T> *counter = list.head;
	if(counter == nullptr){
		return temp;; //list is empty;
	}
	while(counter != nullptr ){
		counter = counter -> next;
		count ++; // Finding size of the list
	}
	Node<T> *spliting = list.head;
	Node<T> *spliting2 = nullptr;
	for(int i = 0; i < count / 2; i ++){
		spliting = spliting -> next; // taking spliter to half
		spliting2 = spliting2 -> next; // taking spliter2 to half - 1
	}
	spliting2 -> next = spliting -> next; //deleting
	delete spliting2;
	
	return temp;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	if(list.head == nullptr){
		return false; //list is empty
	}
	Node<T> *cur = list.head;
	Node<T> *finder = list.head;
	int count = 0;
	while(cur != nullptr){
		cur = cur -> next;
		count ++;// counting list
	}
	for(int i = 0; i < (count - n); i ++){
		finder = finder -> next; // takeing finder to Nth form the end
	}
	return true;

}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	int count = 0;
	Node<T> *cur = list.head;
	Node<T> *prev = nullptr;
	if(cur == nullptr){
		return; // list is empty
	}
	while(cur != nullptr && count < n){
		prev = cur;
		cur = cur -> next;
		count ++; //Get cur to the Nth node. and prev to the previous one.
	}
	prev -> next = cur -> next; // deleting
	delete prev;
	}
	

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
