#include "LinkedListQuestions.h"
#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
    size_t count = 0;
    auto* current = list.head;
    while (current) {
        if (current->data == value)
            ++count;
        current = current->next;
    }
    return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
    auto* head = list.head;
    if (!head || !head->next)
        return;

    auto* newHead = head->next;
    decltype(head) prevTail = nullptr; 

    while (head && head->next) {
        auto* first = head;
        auto* second = head->next;
        auto* nextPair = second->next;

        second->next = first;
        first->next = nextPair;

        if (prevTail)
            prevTail->next = second;

        prevTail = first;
        head = nextPair;
    }

    list.head = newHead;
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
    auto* head = list.head;
    if (!head || k == 0)
        return;

    size_t length = 1;
    auto* tail = head;
    while (tail->next) {
        tail = tail->next;
        ++length;
    }

    k %= length;
    if (k == 0)
        return;

    auto* newTail = head;
    for (size_t i = 1; i < length - k; ++i)
        newTail = newTail->next;
    auto* newHead = newTail->next;
    tail->next = head;
    newTail->next = nullptr;
    list.head = newHead;
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
    auto* head = list.head;
    if (!head)
        return;

    decltype(head) lessHead = nullptr, lessTail = nullptr;
    decltype(head) greaterHead = nullptr, greaterTail = nullptr;

    auto* current = head;
    while (current) {
        auto* next = current->next;
        current->next = nullptr;

        if (current->data < pivot) {
            if (!lessHead)
                lessHead = lessTail = current;
            else {
                lessTail->next = current;
                lessTail = current;
            }
        } else {
            if (!greaterHead)
                greaterHead = greaterTail = current;
            else {
                greaterTail->next = current;
                greaterTail = current;
            }
        }
        current = next;
    }

    if (lessTail)
        lessTail->next = greaterHead;

    list.head = (lessHead) ? lessHead : greaterHead;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);


