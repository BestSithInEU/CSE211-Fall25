// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
    if(list.empty())
        return 0;
    size_t count = 0;
    Node<T>* curr = list.head;
    while (curr != nullptr)
    {
        if (curr->data == value )
            count++;
        curr =curr->next;
    }
    return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {

    Node<T>* prev = nullptr;
    Node<T>* curr = list.head;
    list.head = curr->next;

    while (curr->next != nullptr) {
        Node<T>* nextPair = curr->next->next;
        Node<T>* second   = curr->next;

        second->next = curr;
        curr->next = nextPair;

        if (prev != nullptr)
            prev->next = second;

        prev = curr;
        curr = nextPair;
    }
}



// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {

    while (k > 0) {
        Node<T>* lastNode = list.head;
        Node<T>* beforeLast = nullptr;
        while (lastNode->next != nullptr) {
            beforeLast = lastNode;
            lastNode = lastNode->next;
        }
        if (beforeLast != nullptr ) {
            beforeLast->next = nullptr;
            lastNode->next = list.head;
            list.head = lastNode;
        }
        k--;
    }
}


// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
    LinkedList<T> smaller;
    LinkedList<T> bigger;
    Node<T>* curr = list.head;

    while (curr != nullptr) {
        if (curr->data < pivot)
            smaller.push_back(curr->data);
        else
            bigger.push_back(curr->data);
        curr = curr->next;
    }

    smaller.push_back(pivot);

    Node<T>* tail = smaller.head;
    while (tail->next != nullptr)
        tail = tail->next;

    tail->next = bigger.head;
    list.head = smaller.head;

    smaller.head = nullptr;
    bigger.head = nullptr;
}



// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
