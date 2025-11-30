// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>

// Q1: Get value at Nth position
template <typename T>
bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
  // TODO: Implement your solution here
     Node<T>* cur=list.head;
    size_t lenght=list.count;
    size_t fromstart=index;
    

    
    for(size_t i=0; i<fromstart;i++)
    {
        cur=cur->next;
    }
    

    result = cur->data;
    return true;

}

// Q2: Replace first occurrence
template <typename T>
bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
	
	Node<T>* cur=list.head;
	while(cur!=nullptr)
	{
		if(cur->data==target)
		{
			cur->data=newValue;
			return true;
		}
		
		cur=cur->next;
	}
	
	return false;
  
}

// Q3: Delete all occurrences
template <typename T>
void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  // TODO: Implement your solution here
  Node<T>*cur=list.head;
  Node<T>*toDelete=nullptr;
  Node<T>* prev=nullptr;
  size_t count;
  count=0;
  
  if(cur->data=value)
  {
  	list.head=cur->next;
  	delete cur;
  }
  else{
  	prev=cur;
  	cur=cur->next;
  	
  }
  
  
  while(cur!=nullptr)
  {
  		if(cur->data==value)
  		{
  			prev->next=cur->next;
  			
  			toDelete=cur;
  			cur=cur->next;
  			delete toDelete;
  			count++;
		}
		else
		{
			prev=cur;
			cur=cur->next;
		}
		
  }
 
}

// Q4: Reverse list in-place
template <typename T>
void reverseInPlace(LinkedList<T>& list) {
  Node<T>*cur=list.head;
  Node<T>* temp=nullptr;
  Node<T>* prev=nullptr;
  
  prev=cur;
  cur=cur->next;
  prev->next=nullptr;
  
  while(cur!=nullptr)
  {
  	temp=cur;
  	cur=cur->next;
  	temp->next=prev;
  	prev=temp;
  }
   
  
  list.head=prev;
  
  
  
}

// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);
