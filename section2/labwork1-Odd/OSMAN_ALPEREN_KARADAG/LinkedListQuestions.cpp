// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
    if (list.size() <= 1) {
        return true;
    }

    Node<T>* current = list.head;

    while (current != nullptr && current->next != nullptr) {
        if (current->data > current->next->data) {
            return false;
        }
        current = current->next;
    }

    return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
    LinkedList<T> secondHalf;
    size_t totalCount = list.size();

    if (totalCount <= 1) {
        return secondHalf;
    }
    size_t splitPos = (totalCount + 1) / 2;
    
    Node<T>* current = list.head;
    
    for (size_t i = 0; i < splitPos - 1; ++i) {
        current = current->next;
    }

    if (current != nullptr) {
        secondHalf.head = current->next;
        secondHalf.count = totalCount - splitPos;

        current->next = nullptr;
        list.count = splitPos;
    }
    
    return secondHalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
    size_t totalCount = list.size();

    if (n == 0 || n > totalCount) {
        return false;
    }

    size_t targetPosition = totalCount - n;

    Node<T>* current = list.head;
    
    for (size_t i = 0; i < targetPosition; ++i) {
        current = current->next;
    }

    if (current != nullptr) {
        result = current->data;
        return true;
    }
    
    return false;
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
    if (n == 0 || list.empty()) {
        return;
    }
    
    Node<T> dummy(T(), list.head);
    Node<T>* current = &dummy;
    size_t deletedCount = 0;

    while (current != nullptr && current->next != nullptr) {
        for (size_t i = 0; i < n - 1; ++i) {
            current = current->next;
            if (current == nullptr || current->next == nullptr) {
                
                list.head = dummy.next;
                list.count -= deletedCount;
                return;
            }
        }

        Node<T>* toDelete = current->next; 
        current->next = toDelete->next;    
        delete toDelete;
        deletedCount++;
    }

    list.head = dummy.next;
    list.count -= deletedCount;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
