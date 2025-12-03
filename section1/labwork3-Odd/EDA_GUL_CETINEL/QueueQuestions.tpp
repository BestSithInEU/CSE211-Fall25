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
std::vector<std::pair<T, int>> QueueExt<T>::runLengthEncode() const
{
    std::vector<std::pair<T, int>> result;
    QueueExt<T>temp = *this;
    int count = 1;
    T current = temp.front();
    temp.dequeue();

    while (!temp.isEmpty()) {
        if (temp.front() == current)
        {
            count++;
            temp.dequeue();
        }
        else
        {
            result.emplace_back(current, count);
            count = 1;
            current = temp.front();
            temp.dequeue();
        }
    }
    result.emplace_back(current, count);
    return result;
}

// =============================================================================
// Q2: Josephus survivor - every k-th person is eliminated
// =============================================================================
template <typename T> T QueueExt<T>::josephusSurvivor(int k)
{
    while (this->size()>  1) {
        for (int i = 1; i < k; i++)
        {
            this->enqueue(this->front());
            this->dequeue();
        }
        this->dequeue();
    }
    return this->front();
}

// =============================================================================
// Q3: Generate Binary Numbers using BFS
// =============================================================================
namespace QueueUtils {

template <typename T> Queue<std::string> generateBinaryNumbers(int n)
{
    QueueExt<T> result;
    QueueExt<T> que;
    que.enqueue("1");
    std::string s;

    for (int i = 1; i <= n; i++) {
        s = que.front();
        que.dequeue();

        result.enqueue(s);

        que.enqueue(s + "0");
        que.enqueue(s + "1");
    }
    return result;
}

} // namespace QueueUtils

#endif // QUEUE_QUESTIONS_TPP
