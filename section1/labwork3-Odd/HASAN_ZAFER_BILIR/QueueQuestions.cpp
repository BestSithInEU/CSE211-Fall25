// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
	Queue<T> resultQueue ;
	
	for(int i =0 ; i<= n-k; ++i){ //slicing windows
		int maxVal = speed[i];
		
		for(int j = i , j< i+k-1, ++j){
			
			if(maxVal < speed[j]){
				maxVal = speed[j];
				resultQueue.enqueue(maxVal);
			}
						
			resultQueue.enqueue(maxVal);
		}  
	}	
	
	return resultQueue;
}

} // namespace QueueUtils

// =============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// =============================================================================

template class Queue<int>;
template class Queue<std::string>;

template class QueueExt<int>;
template class QueueExt<std::string>;

template Queue<std::string> QueueUtils::generateBinaryNumbers<std::string>(int);
