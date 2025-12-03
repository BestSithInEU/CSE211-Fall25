// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
  if (list.getSize() <= 1) {
    return true;
  }

  Node<T>* current = list.getHead();
  while (current->next != nullptr) {
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

  if (list.getSize() <= 1) {
    return secondHalf;
  }

  size_t size = list.getSize();
  size_t midIndex = size / 2;

  Node<T>* current = list.getHead();
  for (size_t i = 0; i < midIndex - 1; i++) {
    current = current->next;
  }

  Node<T>* secondStart = current->next;
  current->next = nullptr;

  while (secondStart != nullptr) {
    secondHalf.push_back(secondStart->data);
    secondStart = secondStart->next;
  }

  return secondHalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
  if (n == 0 || n > list.getSize()) {
    return false;
  }

  Node<T>* first = list.getHead();
  Node<T>* second = list.getHead();

  for (size_t i = 0; i < n; i++) {
    first = first->next;
  }

  while (first != nullptr) {
    first = first->next;
    second = second->next;
  }

  result = second->data;
  return true;
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
  if (n <= 1 || list.getSize() == 0) {
    return;
  }

  Node<T>* current = list.getHead();
  size_t count = 1;

  while (current != nullptr && current->next != nullptr) {
    if (count == n - 1) {
      Node<T>* toDelete = current->next;
      current->next = toDelete->next;
      delete toDelete;
      count = 1;
    } else {
      current = current->next;
      count++;
    }
  }
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
