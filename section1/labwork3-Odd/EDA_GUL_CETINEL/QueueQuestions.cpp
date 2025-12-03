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
    int maxValue = 0;
    for (int i = 0; i <= n-k; i++) {
        maxValue = speeds[i];
        for (int j = 1; j < k; j++) {
            if (speeds[i+j] > maxValue) {
                maxValue = speeds[i+j];
            }
        }
        result.push_back(maxValue);
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
