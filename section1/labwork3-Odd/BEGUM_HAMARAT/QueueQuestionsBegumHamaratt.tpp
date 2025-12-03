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
  if(q.empty()) {
    return result;
  }

  std::queue<T> copiedq = q;

  T first = copiedQ.front();
  copiedQ.pop();
  int number =1;

  while(!copiedQ.empty()) {
    T now = copiedQ.front();
    copiedQ.pop();

    if(now == last ){
        number++;
    }
    else{
        now= last;
        number=1
    }
  }

  std::pair<T, int > p;
  p.first = last;
  p.second = number;
  result.push_back(p);

  return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.

  if(k<1) {
    k = 1;
  }

  else if ( this -> isEmpty()) {
    return T();
  }
  else if (this -> size() == 1){
    return this -> dequeue();
  }

  while( this-> size() > 1){  //birden fazla eleman varsa elemeye geçiyoruz
    for( int i = 1 ; i < k ; i++) {
        if(!this -> isEmpty()) {
            T temp = this -> dequeue();
            this -> enqueue(temp);
        }
    }
    this -> dequeue();  // zaten boşsa üstteki döngüden dolayı olmaz
  }
  T last = this -> dequeue();
  return last;
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.

  Queue<std::string> result;  // sonuçların toplandığı yeri oluşturdum

  if( n <= 0) {
    return result;
  }

  int count = 0;
  Queue<std::string> q;  //geçici olarak
  q.enqueue("1");

  if(!q.isEmpty()) {
    string s;
    s = q.dequeue;
    result.enqueue(s);

    count++;

    std:: string x = s+ "0";
    q.enqueue(x);
    std:: string y = s+ "1";
    q.enqueue(y);
  }
  else {

  }
  return result;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
