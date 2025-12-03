// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  if (node == nullptr) return;
  
  displayReverseHelper(node->next, isFirst); 

    if (!isFirst){
    	
	}
    std::cout << node->data;
    isFirst = false;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  // TODO helperi cagir,
  Node<T>* cur = list.head; 
  //displayReverseHelper(cur,true);
  
}

// Q2: Swap adjacent nodes pairwise
// 1 2 3 4 5 
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  // TODO
    
  Node<T>* odd = list.head;
  Node<T>* even = list.head->next;
  
  while(odd != nullptr && even != nullptr){
  	Node<T>* newdup = even->next;
  	
  	even->next = odd;

	if(newdup == nullptr ||newdup->next == nullptr){
		odd->next = newdup;
	}else{
		odd->next = newdup->next;
	}
	
	odd = newdup;
	
	if(odd != nullptr){
		even = odd->next;
	}
	
  }
  
  
  
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	
	if(k==0)return;
	
	
	
}

// Q4: Merge two lists alternately
// 1 2 3     4  5  6      
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
	LinkedList<T> list3;
  	
    Node<T>* head1 = list1.head;
	Node<T>* head2 = list2.head;
	
	while (head1 != nullptr || head2 != nullptr) {

	std::cout << head1->data << "\t" << head2->data << std::endl;
    if(head1->data < head2->data){
    	list3.push_back(head1->data);
    	head1=head1->next;
	}
	else{
		list3.push_back(head2->data);
    	head2=head2->next;
	}
	}
	
	if (head1->next != nullptr){
		
		list3.head->next = head1->next;
	}
	else if(head2->next != nullptr){
		
		list3.head->next = head2->next;
	}
  return list3;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
