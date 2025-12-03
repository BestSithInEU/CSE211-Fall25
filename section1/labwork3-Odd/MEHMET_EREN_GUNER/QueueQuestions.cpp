// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  int n = speeds.size();
  
  if(n==0 || k >n){return result;}
  //
  for(int i=0; i<=n-k; i++){
  	int maxVal = speeds[i];
  	
  	for(int j = i+1; j<i+k; j++){
  		if(speeds[j] >maxVal){maxVal= speeds[j];}
	  }
	  result.push(maxVal);
  }
  return result;
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
