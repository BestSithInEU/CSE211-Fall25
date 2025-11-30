// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	Node<T>* current = list.head;
	int a=0;
	for(size_t i=0;current != nullptr; i++,current = current->next){
		if(current.data == value){
			a++;
		}
	}
	if(a > 0){
		std::cout << "Result: Count = " << a << std::endl;
	}
	else{
		std::cout<< " No any occurrenceses"<<std::endl;
		return 0;
	}
			
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* temp = list.head;
	Node<T>* temp1 = list.head->next;
	Node<T>* temp2 = list.head;
	for(size_t i=0;temp2!= nullptr; i++,temp2 = temp2->next) {
		head = temp1;
		head->next = temp;
		temp = temp1->next;
		temp1 = temp->next;
		
	}
	current-> previous = current;
	std::cout<<"list after swapped: " <<Str list<<std::endl;
	return;
}

// Q3: Rotate list to the right by k positions
template <typename T>
template <typename D>
void rotateRight(LinkedList<T>& list, size_t k) {
	if(k != 0){
		Node<D>* temp1 = head;
		Node<T>* temp = tail;
		int i = 0;
		while(i != k){
			temp = temp->previous;
			i++;
		}
		temp1 = temp;
		temp = temp->previous;
		head = temp1;
		tail = temp;
		std::cout << "rotated list: " << list<< std::endl;
		return;
	}
	std::cout<<"no rotation needed"<<std::endl;
	return;
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	Node<T>* temp = head;
	Node<T>* temp1 = tail;
	Node<T>* temp2 = head;
	for(size_t i =0;temp->next != nullptr; i++){
		if(temp.data < pivot){
			temp2 = temp;
			temp2 = temp2->next;
		}
		else{
			temp1 = temp;
			temp1 = temp1->next;	
		}
		temp=temp->next;
	}
	std::cout<<"The new list after operation is: "<<list<<std::endl;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
