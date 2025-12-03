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
  std::vector<std::pair<T, int>> result;
  if (this->isEmpty())
    return result;

  // We assume QueueExt has access to underlying list/array
  // If not, we dequeue into temp â€” but original queue must remain unchanged.
  Queue<T> temp = *this; // copy does NOT modify original queue

  T prev = temp.dequeue();
  int count = 1;

  while (!temp.isEmpty()) {
    T curr = temp.dequeue();
    if (curr == prev)
      count++;
    else {
      result.push_back({prev, count});
      prev = curr;
      count = 1;
    }
  }
  result.push_back({prev, count});
  return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  if (this->isEmpty())
    throw std::runtime_error("Josephus on empty queue.");

  if (k <= 0)
    throw std::invalid_argument("k must be >= 1");

  while (this->size() > 1) {
    // rotate k-1 times
    for (int i = 1; i < k; ++i) {
      this->enqueue(this->dequeue());
    }
    // eliminate k-th
    this->dequeue();
  }

  return this->dequeue(); // last remaining
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  Queue<std::string> result;
  if (n <= 0)
    return result;

  Queue<std::string> q;
  q.enqueue("1");

  for (int i = 0; i < n; i++) {
    std::string s = q.dequeue();
    result.enqueue(s);

    q.enqueue(s + "0");
    q.enqueue(s + "1");
  }

  return result;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
