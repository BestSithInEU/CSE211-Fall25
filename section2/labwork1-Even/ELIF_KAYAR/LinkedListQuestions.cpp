// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  
  /*
  if (node->next==nullptr && isFirst){
	// push it to stack
	// isFirst = false;
  }
  
  else{
  	displayReverseHelper( node->next, isFirst)
  	//push it to stack
  }
  */
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  
  displayReverseHelper(list.head, isFirst);
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	if (list.head==nullptr){ std::cout << "List is empty" << "\n";
	} else{
		Node<T>* first = list.head;
		Node<T>* second = list.head-> next;
		Node<T>* prev = list.head;
		bool flag = true;
		while (second!=nullptr){
			if(flag){
				first = second->next;
				second = prev->next;
				prev = second;
				flag = false;
		
			}else{
				first = second->next;
				second = prev->next;
				prev = second;
				flag = true;
			}
		}
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  // TODO
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1, const LinkedList<T>& list2) {
	
	LinkedList<T> newList;
	size_t newList.count = list1.size() + list2.size();
	Node<T>* currentFirst = list1.head;
	Node<T>* currentSecond = list2.head;
	Node<T>* currentNew = newList.head;
	while( list1.head != nullptr || list2.head != nullptr){
		currentNew = currentFirst;
		currentFirst = currentFirst->next;
		currentNew = currentNew->next; 
		currentNew = currentSecond->next;
		currentSecond = currentSecond->next;
		currentNew = currentNew->next;
	}
	return newList;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
