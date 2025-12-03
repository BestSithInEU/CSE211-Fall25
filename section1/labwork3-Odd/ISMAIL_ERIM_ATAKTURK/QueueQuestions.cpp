#include <vector>
#include <algorithm>  // std::max

namespace QueueUtils {

std::vector<int> slidingWindowMaximum(const std::vector<int>& speeds, int k) {
    std::vector<int> result;
    int n = static_cast<int>(speeds.size());
    if (n == 0 || k <= 0) {
        return result;  // boÃ¾
    }
    if (k > n) {
        int maxVal = speeds[0];
        for (int i = 1; i < n; ++i) {
            if (speeds[i] > maxVal) {
                maxVal = speeds[i];
            }
        }
        result.push_back(maxVal);
        return result;
    }
    for (int i = 0; i <= n - k; ++i) {
        int maxVal = speeds[i];
        for (int j = i + 1; j < i + k; ++j) {
            if (speeds[j] > maxVal) {
                maxVal = speeds[j];
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
