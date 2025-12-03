// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {

	if (list.size() == 0 || list.size() == 1)
	return true;

	auto* cur = list.head;
	bool ok = true;

	while(cur != nullptr && cur ->next != nullptr){

	if(cur->data > cur->next->data ){

		ok = false;
		break;


	}

	cur = cur ->next;

}

return ok;

 }

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {

LinkedList<T> second;
size_t n  =  list.size();

if(n<=1){

	return second;



}


size_t  firstLen =  (n+1) / 2;

auto* cur = list.head;

for(size_t i = 1 ; i < firstLen  ; i++  ){

	if(cur !=  nullptr)
	cur = cur->next;


}

auto* secondHead = nullptr;
if (cur != nullptr){

	secondHead = cur ->next;
	cur -> next  = nullptr;

}

auto*  p  = secondHead;
while(p!= nullptr){

	second.push_back(p->data);
	p = p ->next;


}


return second;

}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {

if (n == 0)
	return false;

size_t cnt = 0;
auto* t = list.head;

while(t != nullptr ){

	cnt++;
	t = t->next;

}

if(n  > cnt)
	return false;

size_t targetIdx = cnt -n;
auto* cur = list.head;

for( size_t i = 0 ; i < targetIdx    ; i++){


	cur = cur ->next;


}

if(cur== nullptr)
	return false;

result = cur->data;
return true;


}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
