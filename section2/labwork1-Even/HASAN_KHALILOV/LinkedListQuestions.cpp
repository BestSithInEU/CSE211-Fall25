// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
	
	if (node) {
		
    	displayReverseHelper(node->next);
    	cout << node->data;
    	
        if (node->next){
        	cout << " <- ";

		}
	}
	
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
	
    for (Node<T>* node = list.head; node != nullptr; node = node->next) {
        std::cout << node->data;
        if (node->next) {
            std::cout << " -> ";
        }
    }
    std::cout << '\n';
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	Node<T> *cur =  list.head;
	Node<T> *prev = nullptr;
	
	list.head = cur->next;
	
	for(; cur && cur->next; ){
		Node<T> *first = cur;
		Node<T> *sec = cur->next;
		
		if(prev){
			prev->next = sec;
			
			first->next = sec->next;
			sec->next = first;
			
			prev = first;
			cur = first->next;
		}
		
		
	}

}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {

    Node<T>* tail = list.head;
    size_t len = 1;
    for (; tail->next != nullptr; tail = tail->next) {
        ++len;
    }

    k %= len;
    if (k == 0) {
        return;
    }

    tail->next = list.head;

    size_t steps = len - k;
    Node<T>* newTail = list.head;
    for (size_t i = 1; i < steps; ++i) {
        newTail = newTail->next;
    }

    list.head = newTail->next;
    newTail->next = nullptr;
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1, const LinkedList<T>& list2) {
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
