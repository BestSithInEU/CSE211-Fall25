// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
size_t count = 0;

auto*current = list.head;

while(current != nullptr){
	if(current -> data == value ){
		count++;
	}
	current = current -> next;
}    
return count;


}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	if(list.head == nullptr || list.head -> next == nullptr)
		return;
		
		auto*prev = nullptr;
		auto* current = list.head;
		
		list.head = current -> next;
		
		while(current != nullptr && current -> next != nullptr){
			
			auto* first = current;
			auto* second = current -> next;
			
			first -> next = second -> next;
			second -> next = first;
			
			if(prev != nullptr)
			prev -> next = second;
			
			prev = first;
			current = first -> next;
		}
		
	
	
	
	
}

// Q3: Rotate list to the right by k  positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	auto* head = list.head;
	
	if(head == nullptr || head -> next== nullptr)
	return;
	
	if(k == 0)
	return;
	
	size_t n=1;
	
	auto* tail = head;
	
	while( tail -> next != nullptr){
		tail = tail -> next;
		n++;
		
	}
	
	k = k % n;
	
	if( k == 0){
		return;
	}
	
	
	tail -> next = head;
	
	size_t tempstep = n- k-1;
	
	auto* newTail = head;
	
	for(size_t i = 0; i < tempstep; i++){
		
		newTail = newTail->next;
	}
	
	
	list.head = newTail -> next;
	newTail -> next = nullptr;
	
	
}




// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	
	
	
	if( list.head == nullptr || list.head -> next == nullptr)
	return;
		
	
	nodeptr left = nullptr;
	
	auto* current = list.head;
	
	while( current != nullptr ) {
		auto* next = current -> next;
		
		if(current -> data nullptr)
	}
	
	
}











// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
