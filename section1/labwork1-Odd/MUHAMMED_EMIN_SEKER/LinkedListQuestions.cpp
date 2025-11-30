// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Count occurrences of a value
template <typename T>
size_t countOccurrences(const LinkedList<T>& list, const T& value) {
	int count=0;
	Node<T>* temp=list.head;
	while(temp){
		if(temp->data==value){
			count++;
		}
		temp=temp->next;
	}
	return count;
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	Node<T>* prev=nullptr;
	Node<T>*cur=list.head;
	Node<T>* nextNode=nullptr;
	Node<T>* dbprev=nullptr; // prev of prev
	while(cur){
		int i=0;
		while(i<2){
		nextNode=cur->next;
		cur->next=prev;
		dbprev=prev;
		prev=cur;
		cur=nextNode;
		i++;
		}
		dbprev->next=nextNode->next;  
		
	}
}

// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
	if(k>=list.size()||k<1){ //shift sayisinin kosullarini kontrol
		return;
	}
	Node<T>* temp=list.head;
	Node<T>* cur=list.head;
	size_t i=0;
	while(cur->next){
		cur=cur->next; // son nodeu bulus
	}
	while(temp!=nullptr && (i<k)){
		temp=temp->next; //  shift yerine kadar traverse
		i++;
	}
	cur->next=list.head; 
	list.head=temp->next;
	temp->next=nullptr;
	
}

// Q4: Partition around a value
template <typename T>
void partitionAroundValue(LinkedList<T>& list, const T& pivot) {
	LinkedList<T> other1;
	LinkedList<T> other2;
	Node<T>* temp=list.head;
	while(temp){
		if(temp->data<pivot){			//sayilari kontrol edip yerletirme
			other1.push_back(temp->data);
		}
		else{
			other2.push_back(temp->data);
			
		}
		temp=temp->next;
	}
	Node<T>* temp2=other1.head;
		//kucuk sayilarin son nodeunu bulma
	while(temp2->next){
		temp2=temp2->next;
	}
	temp2->next=other2.head;  // birlestrme islemi
	list.head=other1.head;   // ana listeye ekleme
	
	
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template size_t countOccurrences(const LinkedList<int>&, const int&);
template void swapAdjacent(LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
template void partitionAroundValue(LinkedList<int>&, const int&);


// 1 ->  2 >  3 >  4  -->  5  >  6 >  7    8  --  9    10    11   12   NULL

//  4 3 2 1 8 7 6 5 12 11 10 9


/*void swap(){
	Node* prev=nullptr;
	Node*cur=head;
	Node*nextNode=nullptr;
	Node* grouptail=head;
	for(int i=0;i<2&&cur;i++){
		nextNode=cur.next;
		cur.next=prev;
		prev=cur;
		cur=nextNode;
	}
	if(!groupHead){
		groupHead=head;
	}
	if(grouptail!=nullptr){
		grouptail.next=prev;
	}
	grouptail=grouptail.next;
	
	
	
}

void swap(){
	Node* prev=nullptr;
	Node*cur=head;
	Node* nextNode=nullptr;
	Node* lasthead=head;
	nextNode=cur.next;
	cur.next=prev;
	prev=cur;
	cur=nextNode;
	nextNode=cur.next;
	cur.next=prev;
	prev=cur;
	cur=nextNode;
	lasthead.next=nextNode.next;
	w
	
}
// 1 2 3 4 5 6
// 2 1 4 3 6 5 8 7*/




