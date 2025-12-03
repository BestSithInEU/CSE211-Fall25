// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

// Q1: Display list in reverse (recursive helper)
template <typename T>
void displayReverseHelper(Node<T>* node, bool& isFirst) {
  
  if(!node) return 0;
  
  return 1 + displayReverseHelper(node->next, isFirst);
  *(bool*)nullptr;
}

template <typename T>
void displayReverse(const LinkedList<T>& list) {
  
  
  bool isFirst = true;
  int length = displayReverseHelper(list,isFirst);
  
  for(int i = length - 1 ; i>= 0 ; --i){
  	Node<T>* current = list.head;
  	
  	for(int j= 0; j<i ;j++){
  	current = current -> next;
  }
  	
  	if(!isFirst)  std::cout<<' ';
  	std::cout<<current->data;
  	isFalse = false;
  	
  }
  
  std::cout<<'\n';
  
}

// Q2: Swap adjacent nodes pairwise
template <typename T>
void swapAdjacent(LinkedList<T>& list) {
  
  if(list.head == nullptr || list.head -> next == nullptr ) return;
  
  Node<T>* before = nullptr;
  Node<T>* pairNode1 = list.head;
  
  while(!pairNode1 = nullptr && pairNode1 -> next != nullptr ){
  	
  	
  	Node<T> * pairNode2 = pairNode1 -> next;
  	Node<T>* next = pairNode2 -> next;
  	
  	if(before == nullptr){
  		
  		list.head = pairNode2;
	  }
	  else {
	  	before -> next = pairNode2;
	  }
  	
  	
  	pairNode2 -> next = pairNode1;
  	pairNode1 -> next = pairNode2;
  	
  	before = pairNode1;
  	pairNode1 = next;
  }
  
}


// Q3: Rotate list to the right by k positions
template <typename T>
void rotateRight(LinkedList<T>& list, size_t k) {
  
  if( !list.head || !list.head || k == 0) return ;
  
  Node<T> *end = list.head;
  size_t lengthList = 1;
  
  while( end->next != nullptr){
  	
  	end = end->next;
  	lengthList++;
  	
  }
  
  k = k % lengthList;
  if(k ==0) return;
  
  end->next = list.head;
  size_t go1By1 = lengthList - k;
  
  Node<T>* newEnd = list.head;
  
  for(size_t i = 1; i< go1By1 ; i++){
  	
	newEnd = newEnd -> next;
  }
  
  Node<T>* newHead = newEnd -> next;
  newEnd -> next = nullptr;
  list.head = newHead;
  
  
}

// Q4: Merge two lists alternately
template <typename T>
LinkedList<T> mergeAlternately(const LinkedList<T>& list1,
                               const LinkedList<T>& list2) {
  
  LinkedList<T> mixed;
  
  Node<T>* p1 = list1.head;
  Node<T>* p2 = list2.head;
  
  Node<T>* last = nullptr;
  
  
  auto append = [&](const T& value){
  	
  	Node<T>* nNew = new Node<T>{value,nullptr};
  	
  	if(!mixed.head){
  		mixed.head = nNew;
  		last = nNew;
  		
	  }
	  
	  else{
	  	last -> next = nNew;
	  	last = nNew;
	  	
	  }
	  
	}
	  
	  bool take1st = true;
	  
	  while(p1 || p2) {
	  	
	  	if(take1st && p1){
	  		
	  		append(p1 -> data);
	  		p1 = p1 -> next;
		  }
		  
		  else if (!take1st &&  p2){
		  	append (p2 -> data);
		  	p2 = p2 -> next;
		  	
		  }
		  else{
		  	
		  	if(p1){
		  		append(p1->data);
		  		p1 = p1->next;
			  }
			  
			  else if(p2){
			  	append(p2 ->data);
			  	p2 = p2 ->next;
			  }
		  }
		  
		  take1st = !take1st;
	  }
	  
	 
  
   return mixed;
  
}



// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================
template void displayReverse(const LinkedList<int>&);
template void swapAdjacent(LinkedList<int>&);
template LinkedList<int> mergeAlternately(const LinkedList<int>&,
                                          const LinkedList<int>&);
template void rotateRight(LinkedList<int>&, size_t);
