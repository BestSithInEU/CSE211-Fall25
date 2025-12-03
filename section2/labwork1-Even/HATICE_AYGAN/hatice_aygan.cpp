
#include <iostream>

using namespace std;


template <typename T>

void displayReverse(const LinkedList<T>& list) {

	if(list.getSize() == 0){
		
		cout << "please enter a appropriate list." << endl;
	}
	T *current = list.getTail();
	T *first = list.getHead();
	
	cout << current << "->";
	
	if(current != first) {
		
	}
	
}

template <typename T>
void swapAdjacent(LinkedList<T>& list) {
	

	T *current = list.getHead();
	
	
	while(current != nullptr){
		
		T *temp1 = current;
		current -> data = current -> next -> data;
		current -> next -> data = temp;
		
		if(current -> next -> data != nullptr) {
			
			T *temp2 = current -> next -> data;
			current = temp2 -> next -> data;
			
		} else {
			break;
		}
		
	
		
	}
	
}




