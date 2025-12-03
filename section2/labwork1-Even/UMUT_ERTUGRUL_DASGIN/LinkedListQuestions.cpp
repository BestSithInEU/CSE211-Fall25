// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
	if (node == nullptr) return;
	displayReverseHelper(node -> next, isFirst);
	
	if (!isFirst) {
		std::cout << " <- ";
	} else {
		isFirst = false;
	}
	
	std::cout << node -> data;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
	bool isFirst = true;
    displayReverseHelper(list.head, isFirst);
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* temp = list.head;
    if (!temp || !temp -> next) return;

    list.head = temp -> next;
    Node<T>* prev = nullptr;

    while (temp && temp -> next) {
        Node<T>* next = temp -> next;
        Node<T>* nextPair = next -> next;

        next -> next = temp;
        temp -> next = nextPair;

        if (prev) prev -> next = next;

        prev = temp;
        temp = nextPair;
    }
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	if (k == 0 || !list.head || !list.head -> next) return;
	
	Node<T>* tail = list.head;
	size_t len = 1;
	
	while (tail -> next) {
		len++;
		tail = tail -> next;
	}
	
	tail -> next = list.head;
	
	size_t backward = len - k;
    Node<T>* newTail = list.head;
    for (size_t i = 1; i < backward; ++i) {
        newTail = newTail -> next;
    }
    
    list.head = newTail -> next;
    newTail -> next = nullptr;
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
	LinkedList<T> res;
	
    Node<T>* head1 = list1.head;
    Node<T>* head2 = list2.head;
    
    while (head1 || head2) {
    	if (head1) {
    		res.push_back(head1 -> data);
    		head1 = head1 -> next;
		}
		
		if (head2) {
			res.push_back(head2 -> data);
			head2 = head2 -> next;
		}
	}
	
	return res;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
