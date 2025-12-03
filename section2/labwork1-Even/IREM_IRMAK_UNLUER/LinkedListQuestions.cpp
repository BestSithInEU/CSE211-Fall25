// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  if (!node) return;
  
  displayReverseHelper(node->next);
  cout << node->data << " ";
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  displayReverseHelper(list.head);
  cout << endl;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  Node<T>* temp = list.head;
  
  while (temp && temp->next){
  	swap(temp->data, temp->next->data);
  	temp = temp->next->next;
  }
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {

}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
LinkedList<T> result;
Node<T>* p1 = list1,head;
Node<T>* p2 = list2.head;
while(p1 || p2){
	if(p1){
		result.pushBack(p1->data);
		p1 = p1->next;
	}
	if(p2){
		result.pushBack(p2->data);
		p2 = p2->next;
	}
}
return result;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
