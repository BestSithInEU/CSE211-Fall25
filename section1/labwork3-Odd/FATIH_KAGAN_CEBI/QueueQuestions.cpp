#include "QueueQuestions.hpp"
#include <vector>
#include <string>
#include <algorithm> 

namespace QueueUtils {

template <>
Queue<std::string> generateBinaryNumbers<std::string>(int n) {
    Queue<std::string> ciktiKuyrugu;
    
    if (n < 1) return ciktiKuyrugu;

    Queue<std::string> q;
    std::string baslangic = "1";
    q.enqueue(baslangic);

    int sayac = 0;
    
    while (sayac < n) {
        std::string s = q.dequeue();
        
        ciktiKuyrugu.enqueue(s);
        
        std::string sifirli = s + "0";
        std::string birli = s + "1";
        
        q.enqueue(sifirli);
        q.enqueue(birli);
        
        sayac++;
    }

    return ciktiKuyrugu;
}

std::vector<int> slidingWindowMaximum(const std::vector<int> &speeds, int k) {
    std::vector<int> maxHizlar;
    
    int boyut = speeds.size();
    
    if (boyut == 0 || k <= 0) return maxHizlar;

    if (k >= boyut) {
        int enBuyuk = -9999;
        for(int val : speeds) {
            if(val > enBuyuk) enBuyuk = val;
        }
        maxHizlar.push_back(enBuyuk);
        return maxHizlar;
    }

    for (int i = 0; i < boyut; ++i) {
        std::vector<int> pencere;
        
        for (int j = 0; j < k; j++) {
            pencere.push_back(speeds[i + j]);
        }
        
        int enBuyuk = *std::max_element(pencere.begin(), pencere.end());
        maxHizlar.push_back(enBuyuk);
    }

    return maxHizlar;
}

}