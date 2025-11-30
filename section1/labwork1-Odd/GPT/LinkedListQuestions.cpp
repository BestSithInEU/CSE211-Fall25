// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T> &list, const T &value) {
  size_t count = 0;
  auto *curr = list.getHead();

  while (curr) {
    if (curr->data == value)
      count++;
    curr = curr->next;
  }
  return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T> void swapAdjacent(LinkedList<T> &list) {
  auto *head = list.getHead();
  if (!head || !head->next)
    return;

  auto *prev = nullptr;
  auto *curr = head;

  head = head->next; // second node becomes new head
  list.setHead(head);

  while (curr && curr->next) {
    auto *next = curr->next;
    auto *nextPair = next->next;

    // swap
    next->next = curr;
    curr->next = nextPair;

    if (prev)
      prev->next = next;

    prev = curr;
    curr = nextPair;
  }
}

// Q3: Rotate list to the right by k positions
template <typename T> void rotateRight(LinkedList<T> &list, size_t k) {
  if (list.empty() || k == 0)
    return;

  auto *head = list.getHead();
  auto *tail = head;
  size_t length = 1;

  // Find length and tail
  while (tail->next) {
    tail = tail->next;
    length++;
  }

  k = k % length;
  if (k == 0)
    return;

  // Make it circular
  tail->next = head;

  // Find new tail: (length - k - 1) steps from head
  size_t steps = length - k;
  auto *newTail = head;

  for (size_t i = 1; i < steps; i++)
    newTail = newTail->next;

  // New head is next of newTail
  auto *newHead = newTail->next;

  // Break the loop
  newTail->next = nullptr;

  list.setHead(newHead);
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T> &list, const T &pivot) {
  auto *head = list.getHead();
  if (!head)
    return;

  // Two dummy lists: < pivot   and   >= pivot
  Node<T> *lessHead = nullptr;
  Node<T> *lessTail = nullptr;
  Node<T> *geHead = nullptr;
  Node<T> *geTail = nullptr;

  auto *curr = head;

  while (curr) {
    auto *next = curr->next;
    curr->next = nullptr; // detach

    if (curr->data < pivot) {
      if (!lessHead)
        lessHead = lessTail = curr;
      else {
        lessTail->next = curr;
        lessTail = curr;
      }
    } else {
      if (!geHead)
        geHead = geTail = curr;
      else {
        geTail->next = curr;
        geTail = curr;
      }
    }

    curr = next;
  }

  // Join two lists
  if (lessTail)
    lessTail->next = geHead;

  list.setHead(lessHead ? lessHead : geHead);
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int> &, const int &);
template void swapAdjacent(LinkedList<int> &);
template void rotateRight(LinkedList<int> &, size_t);
template void partitionAroundValue(LinkedList<int> &, const int &);
