// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	
	size_t count= 0; 
    Node<T>* temp =head;
    while (temp) {
        if (temp->data==value){
        	count++;
        	temp =temp->next;
		}    
    }
    return count;
}
	



// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	
	
	Node<T>* prev=nullptr;
    Node<T>* curr =head;
    head =curr->next;  
    
	while(curr->next) {
        Node<T>* other= curr->next->next;
        Node<T>* second=curr->next;
        
        second->next =curr;
        curr->next= other; 
	}
	if(){
		
	}
	
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {

    if (k == 0){
    	return;
	}

    while (end->next) {
        end =end->next;
        count++;
    }

    end->next =head;


}



}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {



    if (!head){
    	
    	return;
    	
	} 

    Node<T>* Head1= nullptr;
    Node<T>* End1= nullptr;
    Node<T>* Head2 =nullptr;
    Node<T>* End2 = nullptr;



    Node<T>* curr =head;
    while (curr) {
    	Node<T>* nextone =curr->next;
        curr->next =nullptr;
        if (curr->data<pivot) {
		}
	}


}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);
