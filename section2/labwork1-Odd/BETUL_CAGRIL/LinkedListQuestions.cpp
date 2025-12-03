// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {

    Node<T> *nodePtr = list.head;
    if (!nodePtr){
	}
        return true;

    T currentValue = nodePtr->value;

    
    nodePtr = nodePtr->next;

    while (nodePtr)
    {
        if (currentValue > nodePtr->value)
            return false; 
        currentValue = nodePtr->value;
        nodePtr = nodePtr->next;
    }

    return true; 
}




// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {

   
    LinkedList<T> secondList;

    
    if (list.head == nullptr)
        return secondList;

   
    Node<T> *current = list.head;
    int count = 0;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }

    
    if (count < 2)
        return secondList;

    
    int mid = count / 2;

 
    Node<T> *prev = nullptr;
    current = list.head;
    for (int i = 0; i < mid; i++)
    {
        prev = current;
        current = current->next;
    }

    if (prev != nullptr)
        prev->next = nullptr; 

    
    secondList.head = current;

    return secondList;
}



// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result)
{

    Node<T> *currentNode = list.head;
    Node<T> *behindCurrent = list.head;

   
    if (currentNode == nullptr)
        return false;

 
    for (size_t i = 0; i < n; i++)
    {
        if (currentNode->next != nullptr)
        {
            currentNode = currentNode->next;
        }
        else
        {
            
            return false;
        }
    }

   
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
        behindCurrent = behindCurrent->next;
    }

    
    result = behindCurrent->value;
    return true;
}


// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {






}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
