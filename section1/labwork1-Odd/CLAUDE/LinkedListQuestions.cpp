// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T> &list, const T &value) {
  size_t count = 0;
  Node<T> *current = list.getHead();
  while (current != nullptr) {
    if (current->data == value) {
      count++;
    }
    current = current->next;
  }
  return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T> void swapAdjacent(LinkedList<T> &list) {
  Node<T> *current = list.getHead();
  while (current != nullptr && current->next != nullptr) {
    T temp = current->data;
    current->data = current->next->data;
    current->next->data = temp;
    current = current->next->next;
  }
}

// Q3: Rotate list to the right by k positions
template <typename T> void rotateRight(LinkedList<T> &list, size_t k) {
  if (list.getHead() == nullptr || k == 0) {
    return;
  }

  size_t size = list.getSize();
  k = k % size;
  if (k == 0) {
    return;
  }

  Node<T> *current = list.getHead();
  Node<T> *tail = nullptr;

  while (current->next != nullptr) {
    current = current->next;
  }
  tail = current;
  tail->next = list.getHead();

  size_t stepsToNewTail = size - k;
  current = list.getHead();
  for (size_t i = 1; i < stepsToNewTail; i++) {
    current = current->next;
  }

  list.setHead(current->next);
  current->next = nullptr;
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T> &list, const T &pivot) {
  Node<T> *lessHead = nullptr;
  Node<T> *lessTail = nullptr;
  Node<T> *greaterEqualHead = nullptr;
  Node<T> *greaterEqualTail = nullptr;

  Node<T> *current = list.getHead();
  while (current != nullptr) {
    Node<T> *next = current->next;
    current->next = nullptr;

    if (current->data < pivot) {
      if (lessHead == nullptr) {
        lessHead = current;
        lessTail = current;
      } else {
        lessTail->next = current;
        lessTail = current;
      }
    } else {
      if (greaterEqualHead == nullptr) {
        greaterEqualHead = current;
        greaterEqualTail = current;
      } else {
        greaterEqualTail->next = current;
        greaterEqualTail = current;
      }
    }
    current = next;
  }

  if (lessHead == nullptr) {
    list.setHead(greaterEqualHead);
  } else {
    list.setHead(lessHead);
    lessTail->next = greaterEqualHead;
  }
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int> &, const int &);
template void swapAdjacent(LinkedList<int> &);
template void rotateRight(LinkedList<int> &, size_t);
template void partitionAroundValue(LinkedList<int> &, const int &);
