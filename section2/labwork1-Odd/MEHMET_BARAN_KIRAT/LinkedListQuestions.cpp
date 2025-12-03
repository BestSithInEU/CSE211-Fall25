// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T>
bool isSorted(const LinkedList<T>& list){
	Node<T> *curr1 = list.head;
	Node<T> *curr2 = curr1->next;
	if(curr1==nullptr || curr2 ==nullptr){
		return true;
	}
	while (curr2!=nullptr){
		if(curr1->data <=curr2->data){
			curr1 = curr2;
			curr2 = curr2->next;
		}
		else{
			return false;
		}
		
		
		
	}
	return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
    Node<T> *curr = list.head;
	int length = 0;
	while(curr!=nullptr){
	 length++;
	 curr = curr->next;
	}
	int odd = 0;
	if(length % 2  ==1){
		odd =1;
	}
	LinkedList<int> firsthalf;
	LinkedList<int> secondhalf;
	if(odd==1){
		int index = 0;
		while(index<= (length/2 +1)){
		 firsthalf.push_back(curr->data);
		 curr = curr->next;
		 index++;
	   }
	    while(index <= length){
	    	secondhalf.push_back(curr->data);
	    	curr = curr->next;
	    	index++;
		}
		return secondhalf;
		
	}
	if(odd==0){
		int index = 0;
		while(index<= (length/2)){
		 firsthalf.push_back(curr->data);
		 curr = curr->next;
		 index++;
	   }
		while(index <= length){
	    	secondhalf.push_back(curr->data);
	    	curr = curr->next;
	    	index++;
		}
		return secondhalf;	
		}
		
	}


// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
return false;}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
return;

 
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
