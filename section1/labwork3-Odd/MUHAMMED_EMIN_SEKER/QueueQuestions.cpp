// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  // TODO: Implement This.
  Queue<int> temp,a,b;
  std::vector<int> result;
  size_t sz = speeds.size();
  for(int i=0;i<sz;i++){
  	temp.enqueue(speeds[i]);
  }
  	a=temp;

  while(temp.size()>=k){
  	a=temp;
  	int max=a.front();
  
  	for(int i=0;i<k;i++){
  		if(a.front()>max)max=a.front();
  		a.dequeue();
 	 }
  	result.push_back(max);
 	temp.dequeue();
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
