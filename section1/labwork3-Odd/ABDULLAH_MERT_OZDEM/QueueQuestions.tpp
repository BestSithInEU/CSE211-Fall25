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
std::vector<std::pair<T, int>> QueueExt<T>::runLengthEncode() const{
  std::vector<std::pair<T, int>> encoded;
    if(this->size() == 0){
        return encoded;
    }

    Queue<T> tempQueue = *this;
    T prev = tempQueue.dequeue();
    int num = 1;

    while(!tempQueue.isEmpty()){
        T curr = tempQueue.dequeue();
        if(curr == prev){
            num++;
        } 
	else{
            encoded.push_back({prev, num});
            prev = curr;
            num = 1;
        }
    }
    encoded.push_back({prev, count});
    
    return encoded;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {

T Queue<T>::josephusSurvivor(int k){
    if(this->size() == 0){
        return T();
    }

    if(k == 1){
        while(this->size() > 1){
            this->dequeue();
        }
        return this->dequeue();
    }

    while(this->size() > 1){
        int cnt = 1;

        while (cnt < k){
            T p = this->dequeue();
            this->enqueue(p);
            cnt++;
        }

        T trash = this->dequeue();
    }

    T lastOne = this->dequeue();
    return lastOne;
}


// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  
Queue<std::string> generateBinaryNumbers<std::string>(int n){
    Queue<std::string> result;
    if(n <= 0) return result;
	
    Queue<std::string> tempQueue;
    tempQueue.enqueue("1");

    for (int i = 0; i < n; i++){
        std::string current = tempQueue.dequeue();
        result.enqueue(current);
        tempQueue.enqueue(current + "0");
        tempQueue.enqueue(current + "1");
    }

    return result;
}
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
