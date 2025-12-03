// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
int size = speeds.size();
vector<int> maxes;
for(int i= 0;i<size-(k-1);i++){
	for(int j =i;j<i+k-1;j++){
		int max_v = 0;
			if(max_v<speeds.at(i)){
				max_v = speeds.at(i);
			}
		maxes.push_back(max);
	}
}
return maxes;

	
	
	
  // TODO: Implement This.
}
// hepsini queue ya al. buna temp1 de. bir tane daha al buna temp 2 de ve. onla beraber bir queue da gezin. ve sonra (bosver bunu) 
} // namespace QueueUtils

// =============================================================================
// EXPLICIT TEMPLATE INSTANTIATIONS
// =============================================================================

template class Queue<int>;
template class Queue<std::string>;

template class QueueExt<int>;
template class QueueExt<std::string>;

template Queue<std::string> QueueUtils::generateBinaryNumbers<std::string>(int);
