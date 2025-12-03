// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
  
  if(node == nullptr){
  return;
  }
 
  displayReverseHelper(node->next,isFirst);
  if(isFirst == true){
  std::cout << node->data;
  isFirst = false;
 
  } else{
  std::cout << "-" << node->data;
  }
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  // TODO
	   
	bool isFirst =true;
	if (list.head == nullptr){
	std::cout << "empty list";
	return;
}
	displayReverseHelper(list.head, isFirst);

}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	Node<T> * temp = list.head;
	Node<T> * previous = nullptr;
	
	
	while(temp && temp->next != nullptr ){
		Node<T> * first = temp;
		Node<T> * second = temp->next;
		Node<T> * next = second->next;
		
		
		second->next = first;
		first->next = next;
		
		if(previous != nullptr){
			previous->next = second;
		}
		else{
			list.head = second;
		}
		
		previous = first;
		temp = next;
	}
	
	
	
	
	
  // TODO
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
  Node<T> * temp = list.head;
  int count = 0 ;
  while(temp != nullptr){
  	count++ ;
  	temp = temp->next;	
  }
  
  if(count == 0 || count%k == 0 ){
  	return;
  }

  
  
  
  
  
  
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
  
  LinkedList<T> final;
  
  Node<T> * first = list1.head;
  Node<T> * second = list2.head;
  
  while(first || second != nullptr){
  	
  final.push_back(first->data);
  first = first->next,
  final.push_back(second->data);
  second=second->next;
  }

	return final;
  
  
  
  
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
