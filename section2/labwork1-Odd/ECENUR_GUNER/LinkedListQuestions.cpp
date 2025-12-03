// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	// An empty list or a list with one node is considered sorted.
    if (list.head == nullptr || list.head->next == nullptr) 
        return true; 

    
    Node<T>* current = list.head;

    while (current->next != nullptr) {
        if (current->data > current->next->data) 
            return false;

        current = current->next;
    } 
    
    return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
    LinkedList<T> secondHalf;
    // Handle empty or single-node lists.
    // The original list is unchanged, and an empty list is returned.
    if (list.head == nullptr || list.head->next == nullptr) {
        return secondHalf;
    }
    Node<T>* slow = list.head;
    Node<T>* fast = list.head->next;
    while (fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    secondHalf.head = slow->next;
    slow->next = nullptr;
    size_t originalCount = list.count;
    size_t firstHalfCount = 0;
    Node<T>* current = list.head;
    while (current != nullptr) {
        firstHalfCount++;
        current = current->next;
    }
    list.count = firstHalfCount;
    secondHalf.count = originalCount - firstHalfCount;
    return secondHalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
    if (n == 0 || list.head == nullptr) {
        return false;
    }
    Node<T>* fast = list.head;
    Node<T>* slow = list.head;
    for (size_t i = 0; i < n; ++i) {
        if (fast == nullptr) {
            return false;
        }
        fast = fast->next;
    }
    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    result = slow->data;
    return true;
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
    if (n == 0) 
        return;
    if (n == 1) {
        list.clear();
        return;
    }
    if (list.head == nullptr) 
        return;
    
    Node<T>* current = list.head;
    Node<T>* prev = nullptr;
    size_t counter = 1;
    while (current != nullptr) {
        if (counter % n == 0) {
            Node<T>* toDelete = current;
            if (prev == nullptr) {
                list.head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            delete toDelete;
            list.count--;
        } else {
            prev = current;
            current = current->next;
        }
        counter++;
    } 
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
