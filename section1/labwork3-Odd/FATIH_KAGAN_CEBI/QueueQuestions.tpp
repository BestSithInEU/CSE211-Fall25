#ifndef QUEUE_QUESTIONS_TPP
#define QUEUE_QUESTIONS_TPP

#include "QueueQuestions.hpp"
#include <vector>

template <typename T>
std::vector<std::pair<T, int>> Queue<T>::runLengthEncode() const {
    std::vector<std::pair<T, int>> sonuc;
    
    if (this->isEmpty()) return sonuc;

    Queue<T> kopyaKuyruk = *this;
    std::vector<T> liste;
    
    while(!kopyaKuyruk.isEmpty()) {
        liste.push_back(kopyaKuyruk.dequeue());
    }

    int n = liste.size();
    int i = 0;
    
    while (i < n) {
        T simdiki = liste[i];
        int adet = 1;
        
        int j = i + 1;
        while (j < n && liste[j] == simdiki) {
            adet++;
            j++;
        }
        
        sonuc.push_back(std::make_pair(simdiki, adet));
        
        i = i + adet;
    }

    return sonuc;
}

template <typename T>
T Queue<T>::josephusSurvivor(int k) {
    if (this->size() == 0) return T();

    int sayac = 1;

    while (this->size() != 1) {
        
        if (sayac == k) {
            this->dequeue(); 
            sayac = 1;       
        } else {
            T kisi = this->dequeue();
            this->enqueue(kisi);
            sayac++;
        }
    }

    return this->dequeue();
}

#endif