// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  LinkedList<T>* new_stack = new LinkedList<T>;
  
 
  for(Node<T>* cur = list.head;cur!=nullptr;cur=cur->next){
  
  	new_stack->push_front(cur->data);
  	
	}
  
  new_stack->print();
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
		Node<T>* temp;
		for(Node<T>* cur =list.head;cur!=nullptr;cur=(cur->next)->next){
			temp = cur->next;
			cur->next = temp->next;
			temp->next= cur;
			
			
		}
	
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  LinkedList<T> merged;
  Node<T>* cur1 =list1.head;                          	
  Node<T>* cur2 =list2.head;                          	
  while(cur1 != nullptr || cur2 != nullptr){
  	std::cout << cur1->data << "\t" << cur2->data << std::endl;
  	if (cur1->data < cur2->data){
		merged.push_back(cur1->data);
		cur1 = cur1->next;
	  }
	  else{
  	merged.push_back(cur2->data);
  	cur2 = cur2->next;
	  }
  }
  
  if (cur1 != nullptr){
  	 while(cur1 != nullptr){
  		merged.push_back(cur1->data);
		cur1 = cur1->next;
	  }
	}
  if (cur2 != nullptr){
   while(cur2 != nullptr){
  	merged.push_back(cur2->data);
  	cur2 = cur2->next;
	  }
  }
  return merged;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
