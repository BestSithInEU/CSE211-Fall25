// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  // TODO: Implement This.
  Node* window = this -> head;
  Node* cur = new Node();
  
  while(window -> next != nullptr ){
  	 Node* cur = window;
  	for(int i = 0;i < k; i++){
  		int max = cur -> data;
  		if(max < cur -> data)max = cur->data;
  		cur = cur - >next;
	  }
	speeds.push_back(max);
	for(int j = 0;j<k;j++)window = window -> next;
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
