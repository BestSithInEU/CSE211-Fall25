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
  std::vector<std::pair<T, int>> vct;
  Queue<T>temp=*this;
  int cnt=0;
  T val=temp.front();
  while(!temp.isEmpty()){


    if(temp.front()==val){
        cnt++;
    }
    else{
        std::pair<T,int> p1;
        p1.first=val;
        p1.second=cnt;
        vct.push_back(p1);
        cnt=1;
        val=temp.front();

    }
    temp.dequeue();


  }
  return vct;

}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {

  // TODO: Implement This.
  Queue<T> t =*this;
  while(t.size()!=1){
    for(int i=1;i<k;i++){
        t.enqueue(t.front());
        t.dequeue();

    }
    t.dequeue();
  }
  return t.front();
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
  std::string str = "1";
  Queue<std::string> binq,temp;
  temp.enqueue(str);
  for(int i=0;i<n;i++){
    str=temp.front();
    temp.dequeue();
    binq.enqueue(str);
    temp.enqueue(str+"0");
    temp.enqueue(str+"1");

  }
  return binq;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
