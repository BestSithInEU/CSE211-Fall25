// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
}


 Node<T>* cur = list.head;
  
  if(cur != nullptr)
  {
  	displayReverse(cur->next);
  	std::cout << cur->data << " " ;
  }
  return;


template <typename T>
void displayReverse(const LinkedList<T>& list) {
 
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	if(list.head == nullptr || list.head->next == nullptr )
	{
		return;
	}
	else
	{
		Node<T>* prev= head;
		Node<T>* cur = prev->next;
		Node<T>* curNext = nullptr;
		if(cur->next == list.head)
		{
			list.head = cur;
		}
		while(true)
		{	
			CurNext = cur->next;
			cur->next = prev;
			
			if(curNext == nullptr || curNext->next == nullptr)
			{
				prev->next = curNext;
				break;
			}
			
			prev->next = curNext->next;
			prev = curNext;
			cur = prev->next;
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
