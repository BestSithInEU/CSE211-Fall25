// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T> &list, size_t index, T &result) {
  auto *curr = list.head;
  size_t i = 0;

  while (curr != nullptr) {
    if (i == index) {
      result = curr->data;
      return true;
    }
    curr = curr->next;
    i++;
  }
  return false; // index out of bounds
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T> &list, const T &target, const T &newValue) {
  auto *curr = list.head;

  while (curr != nullptr) {
    if (curr->data == target) {
      curr->data = newValue;
      return true;
    }
    curr = curr->next;
  }
  return false; // not found
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T> &list, const T &value) {
  while (list.head != nullptr && list.head->data == value) {
    auto *tmp = list.head;
    list.head = list.head->next;
    delete tmp;
  }

  auto *curr = list.head;
  while (curr != nullptr && curr->next != nullptr) {
    if (curr->next->data == value) {
      auto *tmp = curr->next;
      curr->next = curr->next->next;
      delete tmp;
    } else {
      curr = curr->next;
    }
  }
}

// Q4: Reverse list in-place
template <typename T> void reverseInPlace(LinkedList<T> &list) {
  Node<T> *prev = nullptr;
  Node<T> *curr = list.head;

  while (curr != nullptr) {
    Node<T> *nextNode = curr->next;
    curr->next = prev;
    prev = curr;
    curr = nextNode;
  }
  list.head = prev;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int> &, size_t, int &);
template bool replaceFirst(LinkedList<int> &, const int &, const int &);
template void deleteAllOccurrences(LinkedList<int> &, const int &);
template void reverseInPlace(LinkedList<int> &);
