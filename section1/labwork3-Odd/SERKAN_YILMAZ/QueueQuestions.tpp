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
  int n = s.length();
  string str = "";

  if(n == 0)
    return str;

  for(int i = 0 ;i < n - 1;i++){

    if(s[i] != s[i + 1]){
        str += s[i];
    }

  }

  str.push_back(s[n-1]);
  return str;

}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {

   for(i=1;i<=k;i++){
		e.enqueue(i);}

	while(k>1)
	{
		for(i=1;i<=k;i++)
			e.move_next();
		d=e.dequeue();
		cout<<d<<endl;
		n--;
	}
	d=e.dequeue();
    }





// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n) {
   vector<string> result;

    for (int i = 1; i <= n; i++) {
        int temp = i;
        string binary = "";

        while (temp > 0) {

            int rem = temp % 2;

            if (rem == 0)
                binary += "0";
            else
                binary += "1";

            temp = temp / 2;
        }

        reverse(binary.begin(), binary.end());

        result.push_back(binary);
    }

    return result;
}

}

#endif // QUEUE_QUESTIONS_TPP
