// include/QueueQuestions.tpp
#ifndef QUEUE_QUESTIONS_TPP
#define QUEUE_QUESTIONS_TPP

#include "QueueQuestions.hpp"
#include <string>
#include <vector>

// =============================================================================
// Q1: Run-length encode - compress consecutive same elements
// =============================================================================
template <typename T>
std::vector<std::pair<T, int>> QueueExt<T>::runLengthEncode() const {
	Queue<T> temp;
	int count = 0 ;
	
	int n = this->size()
	
	for(int i = 0 ;i<n ; ++i){
		temp.enqueue(this->dequeue());
	}
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
	
	std::vector<T> temp ;
	int count = 0;
	
	if (this->size() == 1){// Base case	
		return this->peek();
	}
	
	else{
	
		int index = ((index + k) % this->size());  //finding index
		
		while(count!=index){ // finding removing element
			temp.push_back(this->dequeue());
		}
		
		this->dequeue(); // eliminate the element
		
		while(!temp.empty()){ // refilling the queue
			this->enqueue(temp.pop_back())
		}
		
		return josephusSurvivor(k);	// until 1 element is remaining run whole again
	}		
	
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
	Queue<T> q ;
	q.enqueue("1"); // initiliaze queue
			
	for(int i= 1; i <= n ; ++i){//return binary values 1 to n
		out = q.dequeue(); // find first value				
		std::cout << out;
		out.append("0") // in case second element
		q.enqueue(out);
		out.append("1"); // in case third element
		q.enqueue(out);
	}	
	
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
