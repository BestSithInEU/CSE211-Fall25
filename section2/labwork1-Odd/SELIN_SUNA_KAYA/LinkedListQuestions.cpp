#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Check if list is sorted
template <typename T> bool isSorted(const LinkedList<T> &list) {
	Node* head=list;
	Node* cur=head;
	if(head==NULL||head->next==NULL)return true;
	while(cur->next!=NULL){
		if(cur->data>cur->next->data)return false;
		cur=cur->next;
	}
	return true;
}

// Q2: Split list into two halves
template <typename T> LinkedList<T> splitInHalf(LinkedList<T> &list) {
	Node* head=list;
	Node* cur=head;
	Node* t=cur;
	int count=0;
	while(cur!=NULL){
		count++;
		cur=cur->next;
	}
	cur=head;
	int i=count/2;
	if(count%2==1)i+=1;
	for(int j=0;j<i;j++){
		t=cur;
		cur=cur->next;
	}
	t->next=NULL;
	Node* newhead= cur;
	
	
	
}

// Q3: Find Nth node from end
template <typename T>
bool findNthFromEnd(const LinkedList<T> &list, size_t n, T &result) {
	Node* head=list;
	Node* cur=head; 
	Node t=head;
	int count=0;
	while(cur->next!=NULL){
		count++;
	    while(count>=n)t=t->next;
		cur=cur->next;
	}
	int nthfromtheend= t->data;
	
	
	
	
	
}

// Q4: Delete every Nth node
template <typename T> void deleteEveryNth(LinkedList<T> &list, size_t n) {
	Node* head=list;
	Node* cur=head;
	Node* h;
	Node* t;
	Node* head2;
	Node* null=NULL;
	cur=cur->next;
	while(cur->next->next!=NULL){
		if(cur->data<n){
			head2=cur;
			h=cur;
			t=cur->next;
			h->next=null;
			cur=t;
			null=h;  
		}
		
		cur=cur->next;
		
		
	}
	while(head2->next!=NULL){
		head2=head2->next;
	}
	head2->next=head;
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool isSorted(const LinkedList<int> &);
template LinkedList<int> splitInHalf(LinkedList<int> &);
template bool findNthFromEnd(const LinkedList<int> &, size_t, int &);
template void deleteEveryNth(LinkedList<int> &, size_t);
