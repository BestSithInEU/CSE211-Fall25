// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  std::vector<int> result;
  if (speeds.empty() || k <= 0)
    return result;

  int n = static_cast<int>(speeds.size());
  if (k > n)
    k = n;

  for (int i = 0; i <= n - k; i++) {
    int maxVal = speeds[i];
    for (int j = 1; j < k; j++) {
      if (speeds[i + j] > maxVal) {
        maxVal = speeds[i + j];
      }
    }
    result.push_back(maxVal);
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
