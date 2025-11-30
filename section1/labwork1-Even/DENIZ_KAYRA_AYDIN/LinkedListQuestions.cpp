// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
         
     Node<T>* p = list.head;                      
    size_t i = 0; 

    while (p && i < index) {                        
        p = p->next;
        ++i;
    }

    if (!p) {
    	return false;
	}                           
    result = p->data;                              
    return true;
}


// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	
	const Node<T>* p = list.head;
	 for (Node<T>* p = list.head; p; p = p->next) {
        if (p->data == target) {   
            p->data = newValue;   
            return true;           
        }
    }
    return false;                  
}
  


// Q3 Delete all occurences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
    Node<T>* prev = nullptr;
    for (Node<T>* current = list.head; current != nullptr;) {
        if (current->data == value) {
            if (prev == nullptr) {
                list.head = current->next;
            } else {
                prev->next = current->next;
            }
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        } else {
            prev = current;
            current = current->next;
        }
    }
}



// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
    Node<T>* prev = nullptr;
    Node<T>* current = list.head;
    Node<T>* next = nullptr;

    while (current != nullptr) {
        next = current->next;  
        current->next = prev;
        prev = current;         
        current = next;         
    }

    list.head = prev; 
}


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
