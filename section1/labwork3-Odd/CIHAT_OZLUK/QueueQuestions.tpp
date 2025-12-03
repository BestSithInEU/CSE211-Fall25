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
  std::pair<T,int> p;
  if(head==nullptr){
    cout<<"queue is empty"<<endl;
    return;
  }
  if else(head->next=nullptr){
    p.first=head->data;
    p.second=1;
    cout<<p<<endl;
  }
  else{
    Node *new_node=head;
  while(new_node<=back){
    p.first=new_node->data;
    p.second=1;
    while(new_node==new_node->next){
        p.second++;
        new_node=new_node->next;
    }
    cout<<p<<endl;
    new_node=new_node->next;
    }
  }

}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k) {
    if(k==1){
        while(head->next!=nullptr){
            Queue::dequeue();
        }
        T=Queue.front();
    }
    else if(k>size){
        k=k-size;
        Queue a;
        while(head->next!=nullptr){
            for(int i=0;i<k-1;i++){
                a::enqueue(Queue.dequeue());
            }
            Queue.dequeue();
            while(head!=nullptr){
                a::enqueue(Queue.dequeue());
            }
            while(!a.isEmpty()){
                Queue.enqueue(a.dequeue());
            }
        }

    }
    else{
        Queue a;
        while(head->next!=nullptr){
            for(int i=0;i<k-1;i++){
                a::enqueue(Queue.dequeue());
            }
            Queue.dequeue();
            while(head!=nullptr){
                a::enqueue(Queue.dequeue());
            }
            while(!a.isEmpty()){
                Queue.enqueue(a.dequeue());
            }
        }
    }
    T=Queue.front();
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
