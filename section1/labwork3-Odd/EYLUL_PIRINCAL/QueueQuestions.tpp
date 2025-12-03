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
    int count =0;
    Queue<T> temp= *this;
    T cur=temp.front();
    while(!temp.isEmpty()) {
        T val=temp.front();
        temp.dequeue();
        if (val==cur) {
            count++;
        }
        else {
            current=val;
            count=1;
        }
        return result;
    }



}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.
  if (this->isEmpty()){
    NULL;
  }
    Queue<T> temp= *this;

    while (temp.size()>1) {
        for (int i=1; i<k;i++) {
            temp.enqueue();
            temp.dequeue();
        }
    }
    return temp;
}



// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.



        Queue<T> temp;
        Queue<T> q;
        if (n<= 0){
            return temp;
        }
        q.enqueue("1");
        for (int i = 0; i < n; i++) {
            cur= q.front();
            q.dequeue();
            temp.enqueue(cur);
            return temp;
        }
    }
};


}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
