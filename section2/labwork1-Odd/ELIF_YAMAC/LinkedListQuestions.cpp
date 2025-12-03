// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {}



// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {}

stuck Node {
int veri;
Node *next;
}
Node  *fullist = NULL;
append(fullist, 1)
append(fullist,2)
append(fullist,3)
append(fullist,4)
append(fullist,5)

Node *halflist1 = NULL;
Node *halflist2 = NULL;
Node * templete = head;
int sayi= 0;

	while(templete != NULL){
		sayi++
	 if(sayi <=3){
	 	append(halflist1,templete->veri)
	 }	
	 else{
	 	append(halflist2,templete->veri)
	 }
	 
	}

	


// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
