// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) 
{	
	Node<T>* cur = list.head;
	
	if (!cur || !cur->next) return true;
	while (cur && cur->next) 
{
	
	if (cur->data > cur->next->data) return false;
    cur = cur->next;
}
  return true;  
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) 
{

	LinkedList<T> second;
	
	if (list.count <= 1) return second;

	size_t firstHalfCount = (list.count + 1) / 2;
	size_t secondHalfCount = list.count - firstHalfCount;

	Node<T>* prev = nullptr;
	Node<T>* cur = list.head;
	
	for (size_t i = 0; i < firstHalfCount; ++i) 
{
    prev = cur;
	cur = cur->next;
}

	second.head = cur;
	second.count = secondHalfCount;

	if (prev) prev->next = nullptr;
	
	list.count = firstHalfCount;

	return second;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) 
{
	if (n == 0) return false;

	Node<T>* front = list.head;
	Node<T>* back = list.head;

	for (size_t i = 0; i < n; ++i) 
{
	if (!front) return false;
	front = front -> next;
}
	while (front) 
{
	back = back -> next;
	front = front -> next;
}
	if (!back) return false;
	result = back->data;
	return true;
}

// Q4: Delete every Nth node
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
  Node<T>* lessHead = nullptr;
  Node<T>* lessTail = nullptr;
  Node<T>* geHead = nullptr;
  Node<T>* geTail = nullptr;

  Node<T>* cur = list.head;
  while (cur) {
    Node<T>* nxt = cur->next;
    cur->next = nullptr;

    if (cur->data < pivot) {
      if (!lessHead) { lessHead = lessTail = cur; }
      else { lessTail->next = cur; lessTail = cur; }
    } else {
      if (!geHead) { geHead = geTail = cur; }
      else { geTail->next = cur; geTail = cur; }
    }
    cur = nxt;
  }

  if (lessHead) {
    list.head = lessHead;
    lessTail->next = geHead;
  } else {
    list.head = geHead;
  }
}

template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n)
{
	if (n == 0) return;
	if (n == 1) { list.clear(); return; }

	Node<T>* cur = list.head;
	Node<T>* prev = nullptr;
	size_t idx = 1;

	while (cur) 
{
	if (idx % n == 0) 
{
    	Node<T>* toDelete = cur;
    	if (prev) prev -> next = cur -> next;
    	else list.head = cur -> next;

    	cur = cur -> next;
    	delete toDelete;
    	list.count--;
} 
	else 
{
    	prev = cur;
    	cur = cur -> next;
}
	idx++;
}
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void partitionAroundValue(LinkedList<int>&, const int&);
template void deleteEveryNth(LinkedList<int> &, size_t);
