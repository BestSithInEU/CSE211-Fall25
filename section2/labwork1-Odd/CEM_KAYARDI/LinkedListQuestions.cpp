// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	
	LinkedList *nodePtr;  
   	nodePtr = head;
   	
   	if (nodePtr == NULL || nodePtr->next == NULL) {
        return true;
    }

	while (nodePtr)
	{
	    if(nodePtr->value <= nodePtr->value+1)
	        nodePtr = nodePtr->next;
	    else 
	        return false;
	
	    return true;
	}
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	LinkedList *nodePtr;  
   	nodePtr = head;
	
	LinkedList *dummy1;  
   	dummy1 = nodePtr;
   	
   	LinkedList *dummy2;  
   	dummy2 = nodePtr;
   	
   	while(nodePtr1){
   		dummy1 = dummy1->next;
   		dummy2 = dummy2->next->next;
	   }
	
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	
	LinkedList* dummy = n;
	LinkedList* dummy = new ListNode(0);
	
	dummy->next = head;
    LinkedList* first = head;

    while (first != nullptr) {
    	if(first > )
        first = first->next;
    }

    LinkedList* temp = second->next;
    second->next = second->next->next;
    delete temp;

    return dummy->next;
}
#include "partitionAroundValue.h"

template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {

    Node<T>* lessHead = new Node<T>(T());
    Node<T>* greaterHead = new Node<T>(T());
    Node<T>* lessTail = lessHead;
    Node<T>* greaterTail = greaterHead;

    Node<T>* current = list.head;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (current != nullptr) {
        if (current->data < pivot) {
            lessTail->next = current;
            lessTail = current;
        } else {
            greaterTail->next = current;
            greaterTail = current;
        }
        current = current->next;
    }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
    greaterTail->next = nullptr;
    lessTail->next = greaterHead->next;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    list.head = lessHead->next;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

  
    delete lessHead;
    delete greaterHead;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);

