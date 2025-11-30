// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth poition
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
  
    Node<T>* current = list.head;
    size_t i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        i++;
    }
    if (current == nullptr) return false;

    result = current->data;
    return true;

}

// Q2: Replace first 
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
    for (Node<T>* p = list.head; p; p = p->next) {
        if (p->data == target) {
            p->data = newValue;
            return true;
        }
    }
    return false;
}

// Q3: Delete all 
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
    Node<T>** pp = &list.head;    
    while (*pp) {
        if ((*pp)->data == value) {
            Node<T>* victim = *pp;
            *pp = victim->next;   
            delete victim;
            if (list.count > 0) list.count--;
        } else {
            pp = &((*pp)->next);  
            
            	
			}
	}
}
		

// Q4
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
    Node<T>* prevNode = nullptr;
    Node<T>* cur = list.head;
    while (cur) {
        Node<T>* nxt = cur->next;
        cur->next = prevNode;
        prevNode = cur;
        cur = nxt;
    }
    list.head = prevNode;
}


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
