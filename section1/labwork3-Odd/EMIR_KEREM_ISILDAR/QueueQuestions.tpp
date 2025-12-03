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
  
  std::vector<std::pair<T, int>> encoded;
  if (QueueExt<T>::isEmpty()) {
    return encoded;
  }

  Queue<T> copy(*this);
  while (!copy.isEmpty()) {
    T value = copy.dequeue();
    int count = 1;

    while (!copy.isEmpty() && copy.front() == value) {
      copy.dequeue();
      ++count;
    }

    encoded.push_back({value, count});
  }

  return encoded;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  if (QueueExt<T>::isEmpty()) {
    return T();
  }
  if (k <= 0) {
    k = 1;
  }

  Queue<T> people(*this);
  while (people.size() > 1) {
    for (int i = 1; i < k; ++i) {
      people.enqueue(people.dequeue());
    }
    people.dequeue();
  }

  return people.dequeue();
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

  Queue<std::string> q;
  q.enqueue("1");

  int count = 0;
  while (count < n) {
    std::string front = q.dequeue();
    result.enqueue(front);

    q.enqueue(front + "0");
    q.enqueue(front + "1");

    ++count;
  }

  return result;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
