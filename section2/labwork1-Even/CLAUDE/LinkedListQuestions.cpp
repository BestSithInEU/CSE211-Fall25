// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T> void displayReverseHelper(Node<T> *node, bool &isFirst) {
  if (node == nullptr) {
    return;
  }
  // Recurse to the end first
  displayReverseHelper(node->next, isFirst);
  // Print on the way back (reverse order)
  if (!isFirst) {
    std::cout << " ";
  }
  std::cout << node->data;
  isFirst = false;
}

template <typename T> void displayReverse(const LinkedList<T> &list) {
  bool isFirst = true;
  displayReverseHelper(list.getHead(), isFirst);
  std::cout << std::endl;
}

// Q2: Swap adjacent nodes pairwise
template <typename T> void swapAdjacent(LinkedList<T> &list) {
  Node<T> *current = list.getHead();

  // Swap data of adjacent pairs
  while (current != nullptr && current->next != nullptr) {
    // Swap the data of current and next node
    T temp = current->data;
    current->data = current->next->data;
    current->next->data = temp;

    // Move to the next pair
    current = current->next->next;
  }
}

// Q3: Rotate list to the right by k positions
template <typename T> void rotateRight(LinkedList<T> &list, size_t k) {
  if (list.getHead() == nullptr || list.getHead()->next == nullptr || k == 0) {
    return;
  }

  // Find the length and the tail
  Node<T> *tail = list.getHead();
  size_t length = 1;
  while (tail->next != nullptr) {
    tail = tail->next;
    length++;
  }

  // Normalize k
  k = k % length;
  if (k == 0) {
    return;
  }

  // Find the new tail (length - k - 1 steps from head)
  Node<T> *newTail = list.getHead();
  for (size_t i = 0; i < length - k - 1; i++) {
    newTail = newTail->next;
  }

  // New head is newTail->next
  Node<T> *newHead = newTail->next;

  // Connect old tail to old head
  tail->next = list.getHead();

  // Break the link
  newTail->next = nullptr;

  // Update head
  list.setHead(newHead);
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T> &list1,
                               const LinkedList<T> &list2) {
  LinkedList<T> result;

  Node<T> *ptr1 = list1.getHead();
  Node<T> *ptr2 = list2.getHead();

  // Alternate between list1 and list2
  while (ptr1 != nullptr && ptr2 != nullptr) {
    result.insertAtEnd(ptr1->data);
    result.insertAtEnd(ptr2->data);
    ptr1 = ptr1->next;
    ptr2 = ptr2->next;
  }

  // Append remaining elements from list1
  while (ptr1 != nullptr) {
    result.insertAtEnd(ptr1->data);
    ptr1 = ptr1->next;
  }

  // Append remaining elements from list2
  while (ptr2 != nullptr) {
    result.insertAtEnd(ptr2->data);
    ptr2 = ptr2->next;
  }

  return result;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int> &);
template void swapAdjacent(LinkedList<int> &);
template LinkedList<int> mergeAlternately(const LinkedList<int> &,
                                          const LinkedList<int> &);
template void rotateRight(LinkedList<int> &, size_t);
