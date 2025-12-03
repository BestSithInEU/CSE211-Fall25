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
      std::vector<std::string> subs;
      std::vector<int> numbers;
      result=[{subs,numbers}];
      Node* current=head_;
      while(current->next!=nullptr){
          int counter=1;
          while(current->data==current->next->data){
          counter++;
          current=current->next;
          }
        result.push_back({current->data,counter});
      current=current->next;
      }
      return result;

}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.
  int size1=size();
  while(size1>1){
    int i=1;
    while(k!=i){
        enqueue(front());
        dequeue();
        i++;
    }
    dequeue();
    size1--;
  }
  return head_->data;
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
  std::queue<std::string> temp_queue;
  Queue<std::string> result_queue;
  temp_queue.enqueue("1");
  int counter=1;
  if(counter==n){
    result_queue.enqueue(temp_queue.dequeue());
    return result_queue;
  }
    for (counter; counter < n+1; ++counter) {
        std::string s = generator_queue.front();
        temp_queue.dequeue();
        result_queue.enqueue(s);
        temp_queue.enqueue(s + "0");
        }
    return result_queue;

}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
