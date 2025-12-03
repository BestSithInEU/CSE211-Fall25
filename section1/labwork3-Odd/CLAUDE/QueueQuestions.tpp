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

  QueueExt<T> copy(*this);
  T current = copy.dequeue();
  int count = 1;

  while (!copy.isEmpty()) {
    T next = copy.dequeue();
    if (next == current) {
      count++;
    } else {
      result.push_back({current, count});
      current = next;
      count = 1;
    }
  }
  result.push_back({current, count});

  return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  if (this->isEmpty()) {
    throw std::runtime_error("Cannot find survivor in empty queue");
  }
  if (k <= 0) {
    throw std::runtime_error("k must be positive");
  }

  QueueExt<T> circle(*this);

  while (circle.size() > 1) {
    for (int i = 0; i < k - 1; i++) {
      circle.enqueue(circle.dequeue());
    }
    circle.dequeue();
  }

  return circle.front();
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  Queue<std::string> result;
  if (n <= 0)
    return result;

  Queue<std::string> helper;
  helper.enqueue("1");

  for (int i = 0; i < n; i++) {
    std::string current = helper.dequeue();
    result.enqueue(current);
    helper.enqueue(current + "0");
    helper.enqueue(current + "1");
  }

  return result;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
