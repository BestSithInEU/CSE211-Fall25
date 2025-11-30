#include "LinkedListQuestions.h"
#include <iostream>
#include <vector>

template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  auto current = list.head;
  size_t count = 0;
  while (current != nullptr) {
    if (count == index) {
      result = current->data;
      return true;
    }
    current = current->next;
    ++count;
  }
  return false;
}

template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
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

template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  while (list.head != nullptr && list.head->data == value) {
    auto temp = list.head;
    list.head = list.head->next;
    delete temp;
  }

  auto current = list.head;
  while (current != nullptr && current->next != nullptr) {
    if (current->next->data == value) {
      auto temp = current->next;
      current->next = current->next->next;
      delete temp;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  Node<T>* prev = nullptr;
  auto current = list.head;
  while (current != nullptr) {
    auto nextNode = current->next;
    current->next = prev;
    prev = current;
    current = nextNode;
  }
  list.head = prev;
}

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);

