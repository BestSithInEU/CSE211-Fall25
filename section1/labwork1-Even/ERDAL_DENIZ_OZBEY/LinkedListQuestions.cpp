// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>
template <typename T>
// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T> &list, size_t index, T &result) {
  size_t listLength = list.length();
    if (index >= listLength) {
        return false;
    }
    Node<T>* current = begin();
    size_t currentIndex = 0;
    while (current) {
        if (currentIndex == index) {
            result = current->data;
            return true;
        }
        current = current->next;
        ++currentIndex;
    }
    return false;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  	typename LinkedList<T>::Node* current = list.getNodeAt(0); 
    
    while (current != nullptr) {
        if (current->data == target) {
            
            current->data = newValue;
            return true;  
        }
        current = current->next;
	}
    return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
	if (list.head == nullptr) {
        return;
    }
    while (list.head != nullptr && list.head->data == value) {
        Node<T>* temp = list.head;
        list.head = list.head->next;
        delete temp;
    }
    Node<T>* current = list.head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->data == value) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}
// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
	if(list.head=nullptr||list.head->next=nullptr){
		return;
	}
	else{
		Node<T>* previous = nullptr;
    	Node<T>* current = list.head;
    	Node<T>* next = nullptr;
    	while(current!=nullptr){
    		next = current->next; 
        	current->next = previous; 
        	previous = current; 
        	current = next; 
		}
	}
}
	
  


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
