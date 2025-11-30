// src/LinkedListQuestions.cpp
#include "LinkedListQuestions.h"

#include <iostream>
#include <vector>


template <typename T>
class Node{
	public:
		int deger;
		Node<T>* next;
		
		Node(const T& deger){
			this->deger = deger;
			next = NULL;
		}
};

template <typename T>
class LinkedList{
	private:
		Node<T>* head;
		Node<T>* tail;
		int count;
	public:
		LinkedList(const T& deger){
			Node<T>* node = Node<T>(deger);
			head = node;
			tail = node;
			count++;
		}
		~LinledList(){
			Node<T>* tmp = head;
			while( head != NULL ){
				head = head->next;
				delete temp;
				temp = head;
				count--;
			}
		}
		
		void printList(){
			Node<T>* temp = head;
			while(temp != NULL){
				cout << temp->deger << " ";
				temp = temp->next;
			}
		}
		
		void appendList(const T& deger){
			Node<T>* node = Node<T>(deger);
			tail->next = node;
			tail = node;
			count++;
		}
		// Q1: Get value at Nth position
		template<typename T>
		bool getNthNode(const LinkedList<T>& list, size_t index, T& result) {
		
  		// TODO: Implement your solution here
  		Node<T>* temp = head;
  		if(index < 0 || index > count){
  			result = False;
  			return result;
		  }
		
  		for(int i=0; i<index; i++){
  			temp = temp->next;
  			
		  }
		result = temp;
		return result;
  		
		}
		// Q2: Replace first occurrence
		bool replaceFirst(LinkedList<T>& list, const T& target, const T& newValue) {
  		// TODO: Implement your solution here
  		
  		Node<T>* temp = head;
  		while(temp->value != target){
  			temp = temp->next;
		  }
		if(temp->value != target){
			return NULL;
		}
		  newValue->next = temp->next;
		  target = newValue;
		  delete temp;
  		
  		
		}
		/ Q3: Delete all occurrences
		template <typename T>
		void deleteAllOccurrences(LinkedList<T>& list, const T& value) {
  		// TODO: Implement your solution here
  		
  		Node<T>* temp1 = head;
  		
  		
  		while(temp1 != NULL){
  			Node<T>* temp2= temp1;
  			while(temp2 != NULL){
  				
  				if(temp1->deger == temp2->deger){
  					delete temp2;
				  }
				temp2 = temp2->next;
			  }
			  
		  }
		  temp1 = temp1->next;
			}


		// Q4: Reverse list in-place
		template <typename T>
		void reverseInPlace(LinkedList<T>& list) {
  		// TODO: Implement your solution here
  		
  		
  		for(int i=0; i<count; i++){
  			Node<T>* temp = tail;
  			
  			temp->next = head;
			head = temp->deger;
			delete temp;
			
		  }
  		
  		
  		
		}
		
};












// ============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// ============================================================================

template bool getNthNode(const LinkedList<int>&, size_t, int&);
template bool replaceFirst(LinkedList<int>&, const int&, const int&);
template void deleteAllOccurrences(LinkedList<int>&, const int&);
template void reverseInPlace(LinkedList<int>&);






int main(){
	
	LinkedList<int>* LinkedList1 = new LinkedList<int>(10);
	bool value;
	LinkedList1->appendList(20);
	LinkedList1->appendList(30);
	LinkedList1->appendList(40);
	
	LinkedList1->printList();
	
	if(getNthNode(LinkedList1, 2,value )){
		
	}
	LinkedList1->replaceFirst(LinkedList1, 20, 99);
	LinkedList1->printList();
	
	LinkedList1->appendList(30);
	LinkedList->deleteAllOccucurrences(LinkedList1, 5);
	LinkedList1->printList();
	
	LinkedList1->reverseInPlace(LinkedList1);
	LinkedList1->printList();
	
		
	
	
	
	
	
	
	return 0;
}
