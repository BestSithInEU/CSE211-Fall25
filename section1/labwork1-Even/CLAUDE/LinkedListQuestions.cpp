// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T> &list, size_t index, T &result) {
  auto current = list.head;
  size_t count = 0;
  while (current != nullptr) {
    if (count == index) {
      result = current->data;
      return true;
    }
    count++;
    current = current->next;
  }
  return false;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T> &list, const T &target, const T &newValue) {
  auto current = list.head;
  while (current != nullptr) {
    if (current->data == target) {
      current->data = newValue;
      return true;
    }
    current = current->next;
  }
  return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T> &list, const T &value) {
  while (list.head != nullptr && list.head->data == value) {
    auto temp = list.head;
    list.head = list.head->next;
    delete temp;
  }
  if (list.head == nullptr)
    return;
  auto current = list.head;
  while (current->next != nullptr) {
    if (current->next->data == value) {
      auto temp = current->next;
      current->next = current->next->next;
      delete temp;
    } else {
      current = current->next;
    }
  }
}

// Q4: Reverse list in-place
template <typename T> void reverseInPlace(LinkedList<T> &list) {
  decltype(list.head) prev = nullptr;
  auto current = list.head;
  while (current != nullptr) {
    auto next = current->next;
    current->next = prev;
    prev = current;
    current = next;
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
