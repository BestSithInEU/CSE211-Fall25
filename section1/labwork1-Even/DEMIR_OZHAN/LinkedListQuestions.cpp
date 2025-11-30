// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  Node<T>* curr = list.head;
  int size = 0;
  for(;curr != nullptr;curr = curr->next)
  {
  	size++;
  }
  if(index < 0 || index >= size)
  {
  	return false;
  }
  
  curr = list.head;
  int target = 0;
  while(curr != nullptr)
  {
  	if(target == index)
  	{
  		result = curr->data;
  		return result;
	}
	curr = curr->next;
	target++;
  }
  return 0;
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  Node<T>* curr = list.head;
  while(curr != nullptr)
  {
  	if(curr->data == target)
  	{
  		curr->data = newValue;
  		return true;
	}
	curr = curr->next;
	
  }
  return false;
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  Node<T>* curr = list.head;
  Node<T>* prev = nullptr;
  
  while(curr != nullptr)
  {
  	if(curr->data == value)
  	{
  		if(curr == list.head)
  		{
  			Node<T>* temp = curr;
  			prev = curr;
  			curr = curr->next;
  			list.head = curr;
			
			delete temp;
		}
		else if(curr != list.head || curr->next != nullptr)
		{
			Node<T>* temp = curr;
			prev->next = curr->next;
			delete temp;
			curr = curr->next;
		}
		else if(curr->next == nullptr)
		{
			Node<T>* temp = curr;
			prev->next = nullptr;
			delete temp;
			curr = curr->next;
		}
	}
	else
	{
		prev = curr;
		curr = curr->next;
	}
  }
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  if(list.head != nullptr || list.head->next != nullptr)
  {
  	return;
  }
  
  Node<T>* prev = nullptr;
  Node<T>* curr = list.head;
  Node<T>* next = curr->next;
  
  
  while(next != nullptr){
  	prev = curr;
  	curr = curr->next;
  	next = curr->next;
  	
  }
  
  curr->next = list.head;
   
  list.head = curr;
    
  
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
