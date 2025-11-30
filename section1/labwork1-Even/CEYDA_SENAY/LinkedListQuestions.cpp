// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
	
  // TODO: Implement your solution here
   
    Node<T>* current = head;
	int position = 0 ;
	while (current != nullptr) {
		if (position==size_t index) {
            return current;
        }
        current = current->next;
		position++;
       };

   return -1; 
  
   
 
}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {	
  // TODO: Implement your solution here
  int LinkedList<T>::find(const T& target) const {
    Node<T>* current = head;
    int position = 0;

    while (current != nullptr) {
      if (current->data == value) {
        return position;
      }
      current = current->next;
      position++;
    }

    return -1;  // Not found
  }
   
  void LinkedList<T>::erase(position) {
    if (position >= count || head == nullptr) {
      return;  
    }
    if (position == 0) {
       pop_front();
       return;
    }

    Node<T>* current = head;
    for (size_t i = 0; i < position - 1; i++) {
       current = current->next;
    }

    Node<T>* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
    count--;
   }
  void LinkedList<T>::insert(position, const T& newValue) {
  	
    if (position > count) {
      return;  
    }

    if (position == 0) {
      push_front(value);
      return;
    }

    Node<T>* current = head;
    for (size_t i = 0; i < position - 1; i++) {
      current = current->next;
    }

    Node<T>* newNode = new Node<T>(newValue, current->next);
    current->next = newNode;
    count++;
}
  
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
    while (head == value) {
      Node<T>* temp = head;
      head = head->next;
      delete temp;
    }
    count = 0;
}
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  // TODO: Implement your solution here
  if (head == nullptr) {
    return; 
  }

  Node<T>* temp = head;
  head = head->next;
  Node<T>* current = head;
  while (current->next != nullptr) {
    current = current->next;
  }
  current->next = new Node<T>(temp);
  delete temp;
  
}
  
}
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);

