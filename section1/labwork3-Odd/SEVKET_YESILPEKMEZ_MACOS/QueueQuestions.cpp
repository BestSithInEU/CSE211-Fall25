// src/QueueQuestions.cpp
#include "QueueQuestions.hpp"

#include <vector>

namespace QueueUtils {

// =============================================================================
// Q4: F1 DRS Train Maximum Speed - Sliding Window Maximum
// =============================================================================
std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
  std::vector<int> result;

    int n = speeds.size();

    if ( k > n) {
        return result;
    }

    for (int start = 0; start <= n - k; start++) {

        int currentMax = speeds[start];

        for (int i = start + 1; i < start + k; i++) {
            if (speeds[i] > currentMax) {
                currentMax = speeds[i];
            }
        }

        result.push_back(currentMax);
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
