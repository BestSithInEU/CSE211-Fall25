// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted (non-decreasing order)
template <typename T> bool isSorted(const LinkedList<T> &list) {
  Node<T> *curr = list.getHead();
  if (!curr || !curr->next)
    return true;

  while (curr->next) {
    if (curr->data > curr->next->data)
      return false;
    curr = curr->next;
  }
  return true;
}

// Q2: Split list into two halves
// Return the SECOND HALF, list becomes FIRST HALF
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
  LinkedList<T> second;

  Node<T> *head = list.getHead();
  if (!head || !head->next)
    return second; // nothing to split

  Node<T> *slow = head;
  Node<T> *fast = head;
  Node<T> *prev = nullptr;

  // fast moves 2 steps, slow moves 1 step
  while (fast && fast->next) {
    prev = slow;
    slow = slow->next;
    fast = fast->next->next;
  }

  // slow is the start of the second half
  prev->next = nullptr; // cut the list

  second.head = slow; // assign new list head
  return second;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
  Node<T> *first = list.getHead();
  Node<T> *second = list.getHead();

  // advance first pointer n steps
  for (size_t i = 0; i < n; i++) {
    if (!first)
      return false;
    first = first->next;
  }

  // move both until first hits end
  while (first) {
    first = first->next;
    second = second->next;
  }

  if (!second)
    return false;

  result = second->data;
  return true;
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
  if (n == 0 || n == 1) {
    list.clear();
    return;
  }

  Node<T> *curr = list.getHead();
  Node<T> *prev = nullptr;
  size_t count = 1;

  while (curr) {
    if (count % n == 0) {
      // delete curr
      Node<T> *toDelete = curr;
      curr = curr->next;
      if (prev)
        prev->next = curr;
      else
        list.head = curr;
      delete toDelete;
    } else {
      prev = curr;
      curr = curr->next;
    }
    count++;
  }
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
