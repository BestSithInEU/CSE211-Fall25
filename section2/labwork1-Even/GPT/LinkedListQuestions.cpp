// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// ==============================
// Q1: Display list in reverse
// ==============================

template <typename T> void displayReverseHelper(Node<T> *node, bool &isFirst) {
  if (!node)
    return;

  displayReverseHelper(node->next, isFirst);

  if (!isFirst)
    std::cout << " ";
  std::cout << node->data;
  isFirst = false;
}

template <typename T> void displayReverse(const LinkedList<T> &list) {
  bool isFirst = true;
  displayReverseHelper(list.head, isFirst);
  std::cout << std::endl;
}

// ==============================
// Q2: Swap adjacent nodes pairwise
// ==============================

template <typename T> void swapAdjacent(LinkedList<T> &list) {
  if (!list.head || !list.head->next)
    return;

  Node<T> *prev = nullptr;
  Node<T> *curr = list.head;

  list.head = curr->next; // new head after swap

  while (curr && curr->next) {
    Node<T> *next = curr->next;
    Node<T> *nextPair = next->next;

    // Swap
    next->next = curr;
    curr->next = nextPair;

    // Connect previous pair
    if (prev)
      prev->next = next;

    prev = curr;
    curr = nextPair;
  }

  // Fix tail
  list.tail = list.head;
  while (list.tail && list.tail->next)
    list.tail = list.tail->next;
}

// ==============================
// Q3: Rotate list right by k
// ==============================

template <typename T> void rotateRight(LinkedList<T> &list, size_t k) {
  if (!list.head || k == 0)
    return;

  size_t n = list.size();
  if (n <= 1)
    return;

  k %= n;
  if (k == 0)
    return;

  // Make list circular
  list.tail->next = list.head;

  // Find new tail at position n - k - 1
  Node<T> *newTail = list.head;
  for (size_t i = 0; i < n - k - 1; ++i)
    newTail = newTail->next;

  Node<T> *newHead = newTail->next;

  // Break circle
  newTail->next = nullptr;

  // Set new head and tail
  list.head = newHead;
  list.tail = newTail;
}

// ==============================
// Q4: Merge two lists alternately
// ==============================

template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T> &list1,
                               const LinkedList<T> &list2) {
  LinkedList<T> result;

  Node<T> *a = list1.head;
  Node<T> *b = list2.head;

  while (a || b) {
    if (a) {
      result.push_back(a->data);
      a = a->next;
    }
    if (b) {
      result.push_back(b->data);
      b = b->next;
    }
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
