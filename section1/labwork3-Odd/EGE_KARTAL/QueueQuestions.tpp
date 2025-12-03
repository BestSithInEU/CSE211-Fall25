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
  Queue<T> queue = *this;
  std::vector<std::pair<T, int>> out;
  T prev, cur;
  int length = 0;
  int start = 1;
  while (queue.size() != 0)
  {
	  cur = queue.dequeue();
	  if (cur == prev || start)
		  length++;
	  else
	  {
		  out.push_back(std::pair<T, int>(prev, length));
		  length = 1;
	  }
	  if (start)
		  start = 0;
	  prev = cur;
  }
  out.push_back(std::pair<T, int>(prev, length));
  return out;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  Queue<T> queue = *this;
  while (queue.size() != 1)
  {
	  for (int i = 0; i < (k - 1); i++)
	  {
		  queue.enqueue(queue.dequeue());
	  }
	  queue.dequeue();
  }
  return queue.dequeue();
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  Queue<T> temp;
  Queue<T> out;
  temp.enqueue("1");
  std::string s;
  for (int i = 0; i < n; i++)
  {
	  s = temp.dequeue();
	  out.enqueue(s);
	  temp.enqueue(s + "0");
	  temp.enqueue(s + "1");
  }
  return out;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
