// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
if (list.head==nullptr || list.head->next == nullptr)
return true;
auto cur=list.head;
while(cur->data > cur->next->data){
	if(cur ->data>cur->next->data)
		return false;
	cur=cur->next;	
}
return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
LinkedList<T> secondHalf;
if(list.head==null ptr || list.head->next==null ptr)
return secondHalF;
Node<T>* s=list.head;
node<T>* f=list.head;
Node<T>* prev=nullptr;
while(f!=nullptr && f->next!=nullptr){
	prev=s;
	s=s->next;
	f=f->next->next;
	prev->next=nullptr;
	secondHalf.head=s;
	
	return secondHalf;
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
node *cur=LinkedList.head;


// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
int count=0;
node *cur=LinkedList.head;
node *prev = nullptr;
if(cur==nullptr){
	return;}
	while(cur!=nullptr && count <n){
		prev=cur;
		cur=cur->next
		count++}
		prev->next=cur->next;
		delete
	}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
