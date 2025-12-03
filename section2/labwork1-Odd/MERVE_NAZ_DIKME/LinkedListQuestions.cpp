// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
    using Node = typename LinkedList<T>::Node;
    Node *curr = head;
    
    while (curr->next){
    	if(curr ->data > curr->next->data){
    		return false;
		}
		curr = curr ->next;
	}
	return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
   using Node = typename LinkedList<T>::Node;
   LinkedList<T> secondhalf;
   if(head == nullptr ||head->next ==nullptr){
   	return secondhalf;
   }
   Node<T>* slow = head;
   Node<T> *fast =head->next;
   while(fast->next != nullptr && fast -> next->next != nullptr){
   	slow = slow->next;
   	fast = fast->next->next;
   	
   }
   slow->next = nullptr;
   
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	using Node = typename LinkedList<T>::Node;
	if(n == 0){
		return false;
	}
	int length = 0;
	while(temp != NULL){
		length++;
		temp = temp ->next;
	}
	if(n > length){
		return false;
	}
	for(int i = 0; i < n; i++){
		
	}

}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	using Node = typename LinkedList<T>::Node;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
