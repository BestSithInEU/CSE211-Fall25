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
    std::vector<std::pair<T, int>> result;

    if (this->size() == 0) {
        return result;
    }

    T curr == temp;
    int count = 1;

    for (T size i = 1; i < this->size(); ++i) {

        if (temp->next == curr) {
            count++;
        } else {
            result.push_back({curr, count});

            curr = temp->next;
            count = 1;
        }
    }

    result.push_back({curr, count});

    return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.
  if (this->isEmpty()) {
        cout<< "Queue is empty." << endl;
  }

  else if (k <= 0) {
        cout<< "k is negative." << endl;
  } else {
        for (int i = 1; i < k; i++) {
            this->enqueue(this->dequeue());
        }

        this->dequeue();
    }

    return this->dequeue();
}


// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
Queue<std::string> result;

    if (n <= 0) {
        return result;
    }

    queue.enqueue("1");

    for (int i = 1; i <= n; i++) {
        string s = dequeue.front();

        result.enqueue(s);
        queue.enqueue(s + "0");
        queue.enqueue(s + "1");
    }

    return result;
}

#endif // QUEUE_QUESTIONS_TPP
