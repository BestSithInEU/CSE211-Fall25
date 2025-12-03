// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  // TODO: Implement This.
  vector<int> res;
  
  int n= speeds.size();//arrayin size
  
  for(int i=0;i<=n-k;i++){
  	int max=speeds[i];
  	for(int j=0;j<k;j++){
  		
  		if(speeds[i+j]>max) max=speeds[i+j];
	  }
	  res.push_back(max);
	  
	}
	return res;

  	
  	
  }
  
  
  
  
  
  
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
