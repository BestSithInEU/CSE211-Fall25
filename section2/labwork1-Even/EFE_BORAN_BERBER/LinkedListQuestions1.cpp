// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
	
	if(node == nullptr){
		return;
	}
	
	
	displayReverseHelper(node -> next, isFirst);
	
	
	std :: cout << node -> data << " ";
}
	

template <typename T>

void displayReverse(const LinkedList<T>& list) {
	
	bool iniCtrl = false;
	
	displayReverseHelper<T>(list.getHead(), iniCtrl);
	
	std::cout << std::endl;
	
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  // TODO
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k){
	
	typedef typename LinkedList<T>::Node N;
	
	N* baslangic = list.getHead();
	
	if (baslangic == nullptr || k  == 0){
		return;
	}
	
	

	
	}
	
// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  // TODO
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
