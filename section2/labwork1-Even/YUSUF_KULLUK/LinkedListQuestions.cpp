// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
  
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  // TODO
  Node<T>* curr = list.head;
  LinkedList<T> tempList;
  while(curr != NULL){
  	tempList.push_front(curr->data);
  	curr = curr->next;
  }
  curr = tempList.head;
  while(curr != NULL){
  	std::cout<<curr->data<<" <- ";
  	curr = curr->next;
  }
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  // TODO
  Node<T>* curr = list.head;
  list.head = curr->next;
  Node<T>* temp1 = curr;
  Node<T>* temp2 = curr->next->next;
  while(curr->next != NULL){
  	curr->next = temp1;
  	temp1 = temp2;
  	curr = temp2->next;
  	
  }
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
  
  Node<T>* curr = list.head;
  T temp;
  int i = 0;
  
  while(i<k){
  	while(curr->next != NULL){
  		curr = curr->next;
	  }
	temp = curr->data;
	list.erase(list.find(curr->data));
	
	list.push_front(temp);
	curr = list.head;
	i++;
  }
  
  	
  
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
  Node<T>* curr1 = list1.head;
  Node<T>* curr2 = list2.head;
  LinkedList<T> mergedList;
  
  if(curr1->next != NULL & curr2->next != NULL){
  	mergedList.push_back(curr1->data);
  	mergedList.push_back(curr2->data);
  }
  do{
  	mergedList.push_back(curr1->next->data);
  	mergedList.push_back(curr2->next->data);
  	curr1 = curr1->next;
  	curr2 = curr2->next;
  }while(curr1->next != NULL & curr2->next != NULL);
  
  while(curr1->next != NULL){
  	mergedList.push_back(curr1->next->data);
  	curr1 = curr1->next;
  }
  
  while(curr2->next != NULL){
  	mergedList.push_back(curr2->next->data);
  	curr2 = curr2->next;
  }
  
  return mergedList;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
