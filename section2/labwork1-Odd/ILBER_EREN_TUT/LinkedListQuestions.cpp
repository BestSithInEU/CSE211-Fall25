
/ src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

bool isSorted(LinkedList<T>* list){

    LinkedListT temp = list;

    while(temp->next != nullptr){
        if(temp->data > temp->next->data){
            return false;
          }
    temp=temp->next;
         }
return true;
}

void splitInHalf(LinkedList<T>* list){

    LinkedListT *secondHalf;

        if(list.size() <= 1){
            return secondHalf;
        }
    int mid = (list.size()+1)/2
 
    node<T> * curr = list.head;
    node<T> * prev = nullptr;

    for(int i=0;i<mid; i = i + 1){
            prev=curr;
            curr=curr->next;

        }

    secondHalf.head=curr
    secondHalf.tail=list.tail;
    secondHalf._size=list._size - mid;

    if(prev){ 
        prev->next = nullptr;
        last.tail;
        last._size=mid;
        return secondHalf;
            }
}

bool findNthFromEnd(const LinkedList<T> *list, size_t 
    if (n==0  n>list.size())
        return false;

Node<T> * first = list.head;
Node<T> * second = head;

for (size_t i = 0; i<n; ++i){


// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
