// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"
#include <stack>

// Q1: Display list in reverse (recursive helper)

template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
  
  	if (!node){
  		return;
	}
	
    displayReverseHelper(node->next, isFirst);
    if (!isFirst) {
    	std::cout << " <- ";	
	}
	
    std::cout << node->data;
    
    isFirst = false;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
	
    bool isFirst = true;
    displayReverseHelper(list.head, isFirst);
    std::cout << std::endl;
}

// Q2: Swap adjacent nodes pairwise
//Helper kullandim kodu recursive yapabilmek iÃ§in
template <typename T>
Node<T>* swapAdjacentHelper(Node<T>* head) {
    if (!head || !head->next)
        return head;

    Node<T>* first = head;
    Node<T>* second = head->next;
    Node<T>* nextPairHead = second->next;

    second->next = first;
    first->next = swapAdjacentHelper(nextPairHead);

    return second;
}

template <typename T>
void swapAdjacent(LinkedList<T>& list) {
    list.head = swapAdjacentHelper(list.head);
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
    LinkedList<T> result;
    Node<T> dummy(T{});   
    Node<T>* curr = &dummy;

    Node<T>* list1P = list1.head;
    Node<T>* list2P = list2.head;

    while (list1P || list2P) {
        if (list1P) {
            curr->next = new Node<T>(list1P->data);
            curr = curr->next;
            list1P = list1P->next;
        }
        if (list2P) {
            curr->next = new Node<T>(list2P->data);
            curr = curr->next;
            list2P = list2P->next;
        }
    }

    result.head = dummy.next;
    return merged;
}


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
