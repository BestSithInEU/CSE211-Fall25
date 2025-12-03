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
temp<queue> == QueueExt;
string answer;

for(int i = 0;i<=size(temp);i++){
temp.front = answer;
	if(answer == T){
		T.second++;}
	temp.pop;
}

  // TODO: Implement This.
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
vector<string> death_circle;
int size_q = QueueExt.size();
	for(int i=0;i<size_q;i++){
	death_circle.pushback(QueueExt.front);
		QueueExt.pop;
	}
while(size_v != 1){
int size_v = death_circle.size();
for(int j=0;j<size_v;j++){
if(j % k=0;){
death_circle.erase(j);}
}


  // TODO: Implement This.
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
  // TODO: Implement This.
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
