// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value){
    size_t k =0;
    auto n = list.getHead();
    
    while(n !=nullptr){
    	
        if(n->data == value) k++;
        n = n->next;
        
    }
    return c; 
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list){
	
    if(!list.getHead() || !list.getHead() ->next) return;
    auto swap = new Node<T>();
    swap->next = list.getHead();
    
    auto p = swap;
    while(p->next && p->next->next){
    	
        auto a = p->next;
        auto b = p->next->next;
        a->next = b->next;
        b->next = a;
        p->next = b;
        p=a;
    }
    list.setHead(swap -> next);
    delete swap;
}
}

// Q3: Rotate list to the right by k positions
template <typename T>

void rotateRight(LinkedList<T>& list, size_t k){
	
    if(!list.getHead()) return;
    auto curr = list.getHead();
    size_t long = 1;
    while(curr->next) {
        long++;
        curr = curr->next;
    }
    
    k = k % long;
    if(k == 0) return;
    curr->next = list.getHead();
    
    size_t stepsNewTail = long - k; 
    auto newTail = list.getHead();
    for(size_t i = 1; i < stepsNewTail; i++) {
        newTail = newTail->next;
    }
    auto newHead = newTail->next;
    newTail->next = nullptr;
    
    list.setHead(newHead);
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot){
	
    if(!list.getHead()) return;
    Node<T>* lessHead = nullptr;
    Node<T>* lessTail = nullptr;
    auto curr = list.getHead();


// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
