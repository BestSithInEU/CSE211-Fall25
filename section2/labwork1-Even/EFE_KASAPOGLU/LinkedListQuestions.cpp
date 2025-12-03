// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"
#include <iostream>
#include <stack>


// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  if (node == nullptr) {
        return;
    }

    displayReverseHelper(node->next, isFirst);
    if (!isFirst) {
     };
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
   if (list.head == nullptr || list.head->next == nullptr) {
        return;
    }

    Node<T>* newHead = list.head->next;
    Node<T>* prev = nullptr; 
    Node<T>* current = list.head; 

    while (current != nullptr && current->next != nullptr) {
        Node<T>* first = current;         
        Node<T>* second = current->next;  

        first->next = second->next; 
        
        second->next = first;             
        
        if (prev != nullptr) {
            prev->next = second;
        }
        
        prev = first;
        current = first->next;
    }

    list.head = newHead; 
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  if (list.head == nullptr || k == 0) {
        return;
    }

    Node<T>* basla = list.head;
    size_t len = 1;
    while (basla->next != nullptr) {
        basla = basla->next;
        len++;
    }

    size_t actualK = k % len;

    if (actualK == 0) {
        return;
    }
    size_t stepsToNewBasla = len - actualK - 1; 

    Node<T>* newBasla = list.head;
    for (size_t i = 0; i < stepsToNewBasla; i++) {
        newBasla = newBasla->next;
    }
    basla->next = list.head;

    list.head = newBasla->next; 

    newBasla->next = nullptr;
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  LinkedList<T> mergedList; 
    
    Node<T>* current1 = list1.head;
    Node<T>* current2 = list2.head;

    while (current1 != nullptr || current2 != nullptr) {
        
        if (current1 != nullptr) {
            mergedList.push_back(current1->data); 
            current1 = current1->next;
        }
        if (current2 != nullptr) {
            mergedList.push_back(current2->data); 
            current2 = current2->next;
        }
      }

    return mergedList;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
