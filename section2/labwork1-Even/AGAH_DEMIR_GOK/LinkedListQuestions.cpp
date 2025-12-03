// include/LinkedListQuestions.h
#ifndef LINKEDLIST_QUESTIONS_H
#define LINKEDLIST_QUESTIONS_H

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include "LinkedList.h"
#include <stack>

// Q1: Display the list in reverse order without modifying it
template <typename T>
void displayReverse(const LinkedList<T>& list) {
    if (list.head == NULL) {
        cout << "its empty" << endl;
        return;
    }
    stack<T> s;
    temp = list.head;
    while (temp) {
        s.push(temp->data);
        temp = temp->next;
    }
    while (!s.empty()) {
        cout << s.top();
        s.pop();
        if (!s.empty()) cout << " <- ";
    }
    cout << endl;
}


// Q2: Swap every two adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
    if (!list.head || !list.head->next) return;
    prev = nullptr;
     curr = list.head;
    list.head = curr->next;
    while (curr && curr->next) {
        next = curr->next;
        curr->next = next->next;
        next->next = curr;
        if (prev) prev->next = next;
        prev = curr;
        curr = curr->next;
    }
}
// Q3: Merge two lists alternately (1st from list1, 1st from list2, etc.)
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
    if (!list.head || k == 0) return;
    tail = list.head;
    size_t len = 1;
    while (tail->next) {
        tail = tail->next;
        len++;
    }
    k %= len;
    if (k == 0) return;
    tail->next = list.head;
    size_t steps = len - k;
    auto newTail = list.head;
    for (size_t i = 1; i < steps; ++i) newTail = newTail->next;
    list.head = newTail->next;
    newTail->next = NULL;
}
// Q4: Rotate the list to the right by k positions
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1, const LinkedList<T>& list2) {
    LinkedList<T> merged;
    a = list1.head;
    b = list2.head;
    while (a || b) {
        if (a) {
            merged.push_back(a->data);
            a = a->next;
        }
        if (b) {
            merged.push_back(b->data);
            b = b->next;
        }
    }
    return merged;
}
#endif  // LINKEDLIST_QUESTIONS_H
