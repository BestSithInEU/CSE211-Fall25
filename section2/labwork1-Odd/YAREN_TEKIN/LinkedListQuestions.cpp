// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	if (list.head == nullptr || list.head->next == nullptr)
return true;

auto nodePtr = list.head;
while (nodePtr->next != nullptr) {
if (nodePtr->data > nodePtr->next->data)
return false;
nodePtr = nodePtr->next;
}
return true;
}


// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	LinkedList<T> secondHalf;
   if (list.head == nullptr || list.head->next == nullptr)
return secondHalf;

auto slow = list.head;
auto fast = list.head;
auto midPrev = list.head;


while (fast != nullptr && fast->next != nullptr) {
midPrev = slow;
slow = slow->next;
fast = fast->next->next;
}


midPrev->next = nullptr;
secondHalf.head = slow;

return secondHalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
if (n == 0)
return false;

auto lead = list.head;
auto follow = list.head;


for (size_t step = 0; step < n; ++step) {
if (lead == nullptr)
return false;
lead = lead->next;
}


while (lead != nullptr) {
lead = lead->next;
follow = follow->next;
}

result = follow->data;
return true;


}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	void deleteEveryNth(LinkedList<T> &list, size_t n) {
    if (!list.head || n == 0)
        return;

    Node<T>* current = list.head;
Node<T>* prev = nullptr;
size_t index = 1;

while (current != nullptr) {
if (index % n == 0) {
Node<T>* toRemove = current;

if (prev == nullptr)
list.head = current->next;
else
prev->next = current->next;

current = current->next;
delete toRemove;
} else {
prev = current;
current = current->next;
}
++index;
    }

}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
