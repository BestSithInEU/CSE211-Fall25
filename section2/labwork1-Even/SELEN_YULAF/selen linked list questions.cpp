// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
      if (node == NULL) return;
    displayReverseHelper(node->next, isFirst);
    if (!isFirst) {
        cout << " <- ";
    }
    cout << node->data;
    isFirst = false;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
    vector<T> arr;
    Node<T>* temp = list.head; 

    while (temp != NULL) {
        arr.push_back(temp->data);
        temp = temp->next; 
    }

    int i = arr.size() - 1;
    while (i >= 0) {
        cout << arr[i] << " ";
        i = i - 1;
    }

    cout << endl; 

}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  Node<T>* temp = list.head;
   while (temp != NULL) {
       if (temp->next == NULL) {
           temmp=temp->next;
    }
        else { 
        T d
        d = temp->data;
        temp->data = temp->next->data;
        temp->next->data = d;
        temp = temp->next->next;
           
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
