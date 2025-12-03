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
    Node* cur = this->head_;
    T currentValue = cur->data;
    int count = 0;
    while (cur != nullptr) {
        if (cur->data == currentValue) {
            count++;
        } else {
            result.push_back({currentValue, count});
            currentValue = cur->data;
            count = 1;
        }
        cur = cur->next;
    }
    result.push_back({currentValue, count});
    return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.

  this.dequeue();
  while(this.size() != 1){
    for(int i = 0; i<k-1;i++){
        int shift = this.dequeue();
        this.enqueue(shift);
    }
    this.dequeue();
  }
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
  cout << "[";
    for(int i = 0; i<n ; i++){
        while(n > 1){
            string s = "";
            if(n/2 == 1){
                s = "1" + s
            }else if(n/2 == 0){
                s = "0"+ s;
            }
            n%=2;
        }
        if(n==1){
            cout << "1"+s<<" ";
        }else if(n==0){
            cout << "0"+s<<" ";
        }
    }
    cout << "]";
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
