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
  std::vector<std::pair<std::string,int>> result;
  while(!QueueExt.isempty()){
  
  for
  result(QueueExt.pop();
  
  
  
  
  
}
  
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
  // TODO: Implement This.
  
  QueueExt<T> q1;
  while(this->q.size()!=1){
  
  while(this->q.isempty()){
  
  for(int i=1;i<k;i++){
  
  q1.push_back();
  
}
this->q.pop();

while(q1.isempty()){
for(int i=1;i<k;i++){
this->q.push_back();
}
q1.pop();
}


}

retrun this->q;

}
  
  
  
  
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
  
  std::vector<std::string> result;
  
  
  for(int number=1;number<=n;number++){
  int temp=number;
  string binary="";
  
  while(temp>0){
  int remain=temp%2;
  
  if(remanin==0){
  binary+="0";}
  else{
  binary+="1";
  }
  temp=temp/2;
  }
  
  reverse(binary.begin(),binary.end());
  result.push_back(binary);

}
return result;
  
  
}
  
  
  
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
