// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  std::vector<int> out;
  int max;
  int remainder_part = speeds.size() % k;
  for (size_t i = 0U; i < (speeds.size() - remainder_part); i++)
  {
	  max = speeds[i];
	  for (int j = 0U; j < k; j++)
	  {
		  if (speeds[i + j] > max)
			  max = speeds[i + j];
	  }
	  out.push_back(max);
  }
  return out;
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
