// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  // TODO
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
   Node *head;
   stack<Node *> stack1;
   Node* pointer = head;
    while (pointer->next != NULL) {
        stack1.push(pointer);
        pointer = pointer->next;
    }
	head = pointer;
    
    while (!stack1.empty()) {
        pointer->next = stack1.top();
		pointer = pointer->next;
        stack1.pop();
    }
    
    pointer->next = NULL;
    
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  Node<T>* current = list.head;
   while (current != NULL && current->next != NULL) {
       T tempValue = current->data;
       current->data = current->next->data;
       current->next->data = tempValue;
       current = current->next->next;
   }
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  if (list.head == NULL || k == 0){
  		return;
   } 
   int count;
   Node<T>* tail = list.head;
   for(count = 1; tail->next != NULL; count++){
		temp = temp->next;
   }
   tail ->next = list.head;
   
   k = k % count;
   if(k == 0){
   	return;
   }
   int step = count - k;
   Node<T>* tail2 = list.head;
   int j = 1;
   while(j < step){
   		tail2 = tail2->next;
   		j++;
   }
   
   list.head = tail2->next;
   tail2->next = NULL;
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  LinkedList<T> final;
   Node<T>* t1 = list1.head;
   Node<T>* t2 = list2.head;
   Node<T>* last = nullptr;
   while (t1 != NULL || t2 != NULL) {
       if (t1 != NULL) {
           result.push_back(t1->data);
           t1 = t1->next;
       
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
