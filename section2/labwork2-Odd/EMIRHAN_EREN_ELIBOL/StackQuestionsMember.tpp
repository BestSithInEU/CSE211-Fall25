#ifndef STACK_QUESTIONS_MEMBER_TPP
#define STACK_QUESTIONS_MEMBER_TPP

#include "StackQuestionsMember.h"
#include <vector>
#include <set>

template <typename T>
bool StackQuestions<T>::isPalindrome() const {
    if (this->isEmpty() || this->size() == 1) {
        return true;
    }

    StackQuestions<T> tmp(*this);

    std::vector<T> elems;
    elems.reserve(tmp.size());
    while (!tmp.isEmpty()) {
        elems.push_back(tmp.top());
        tmp.pop();
    }

    std::size_t i = 0;
    std::size_t j = elems.size() - 1;
    while (i < j) {
        if (!(elems[i] == elems[j])) {
            return false;
        }
        ++i;
        --j;
    }

    return true;
}

template <typename T>
void StackQuestions<T>::removeDuplicates() {
    if (this->isEmpty() || this->size() == 1) {
        return;
    }

    std::vector<T> elems;
    elems.reserve(this->size());
    while (!this->isEmpty()) {
        elems.push_back(this->top());
        this->pop();
    }

    std::set<T> seen;
    std::vector<T> filtered;
    filtered.reserve(elems.size());

    for (const T &value : elems) {
        if (seen.insert(value).second) {
            filtered.push_back(value);
        }
    }

    for (auto it = filtered.rbegin(); it != filtered.rend(); ++it) {
        this->push(*it);
    }
}

#endif
