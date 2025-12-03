// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
  std::cout<<node->data;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  // TODO
  displayReverseHelper(list.head,isFirst);
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  // TODO
  Node<T>* prev = NULL;
  Node<T>* curr = list.head;
  list.head = curr->next;
  while(curr){
	Node<T>* a = curr->next->next;
  	Node<T>* b = curr->next;
  	b->next = curr;
  	curr->next = a;
  	if(prev) {
  		prev->next = b;
	}
  	prev = curr;
  	curr = a;
  }
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
  if(!list.head){
  	return;
  }
  k = k % list.size();
  if(k == 0){
  	return;
  }
  size_t count = 0;
  while(list.head->next){
  	head = head->next;
  	count++;
  }
  for(size_t i=0;,<n - k;i++){
  	a = a->next;
  }
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
  LinkedList<T> mergedlist;
  Node<T>* tail1=list1.head;
  Node<T>* tail2=list2.head;
  if(tail1 !=NULL && tail2 == NULL){
  	mergedlist.push_back(t1->data);
  	tail1 = tail1->next;
  }
  else if(tail2 != NULL){
  	mergedlist.push_back(t2->data);
  	tail2 = tail2->next;
  }
  return mergedlist;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
