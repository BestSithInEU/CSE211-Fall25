// include/QueueQuestions.tpp
#ifndef QUEUE_QUESTIONS_TPP
#define QUEUE_QUESTIONS_TPP

#include "QueueQuestions.hpp"
#include <string>
#include <vector>

// =============================================================================
// Q1: Run-length encode - compress consecutive same elements
// =============================================================================
template <typename T>
std::vector<std::pair<T, int>> QueueExt<T>::runLengthEncode() const {
  // TODO: Implement This.
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  int step = k - 1;

  while (step > 0) {
    T frontItem = this->dequeue();
    this->enqueue(frontItem);
    step--;
  }
  return this->dequeue();
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  Queue<std::string> result;

    if (n <= 0) {
        return result;
    }

    Queue<std::string> s;
    Queue<std::string> q;
    
    q.enqueue("1");


    for (int i = 0; i < n; i++) {
        s = q.dequeue();
        result.enqueue(s);

        q.enqueue(s + "0");
        q.enqueue(s + "1");
    }

    return result;
}
  

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
