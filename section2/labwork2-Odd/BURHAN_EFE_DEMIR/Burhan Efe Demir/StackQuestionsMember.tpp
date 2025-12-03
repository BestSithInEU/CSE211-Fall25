#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"

// ============================================================================
// Question 1: isPalindrome
// ============================================================================
template <typename T> bool StackQuestions<T>::isPalindrome() const {
  // TODO: Implementation

  // bos stack polindromdur
  if (internalStack.empty()) {
    return true;
  }

  // orijinal stack'i ("internalStack") bozamayiz (const kurali) o yuzden kopyasini alip icini bosaltiriz
  std::stack<T> tmp = internalStack;

  //verileri rahat kontrol etmek icin bir diziye dokuyoruz
  std::vector<T> vec;
  while (!tmp.empty()) {
    vec.push_back(tmp.top());
    tmp.pop();
  }
  // simdi klasik palindrom kontrolu yapiyorum yani bastan ve sondan yaklasmak
  int sol = 0;
  int sag = vec.size() - 1;

  while (sol < sag) {
    // eger bastaki ve sondaki esit degilse, palindrom degildir
    if (vec[sol] != vec[sag]) {
        return false;
    sol++; // sola kaymasi icin
    sag++; //saga kaymasi icin
    }
    return true;
  }
}

// ============================================================================
// Question 2: removeDuplicates
// ============================================================================
template <typename T> void StackQuestions<T>::removeDuplicates() {
  // TODO: Implementation
  // ilk olarak kimlerin goruldugunu bakacagiz liste yapacagiz
  std::stack<T> res;

  // kontrol islemleri icin temp kullaniyorum
  std::stack<T> tmp;

  // ana elemanlari bitirene kadar eleman aliyoruz
  while (!internelStack.empty())){
  T val = internalStack.top();
  internalStack.pop()
  }

  // val degeri res icinde var mi
  bool varMi = false;

  // bunun icin res stack'ini tmp'ye bosaltip icine bakiyorum
  while (!res.empty()){
    if(res.top() == val){
        varMi = true; // burada var, demek ki kopyasi
    }
    tmp.push(res.top()); //bakarken kaybetmemek icin tmp'ye atiyorum
    res.pop();
  }
  // simdi res'i eski haline getiriyorum
  while (!tmp.empty()) {
    res.push(tmp.top());
    tmp.pop();
  }
  //eger icinde aynisindan yoksa res'e ekle
  if (!varMi) {
    res.push(val);
  }

  // 3. dongu bittiginde res icinde sadece benzersiz olanlar var ancak stack mantigi yuzunden siralama ters dondu
  // res'i ana stack'e bosaltirsak siralama duzelir
  while (!res.empty()) {
    internalStack.push(res.top());
    res.pop();
  }


}

#endif // STACK_QUESTIONS_MEMBER_TPP
