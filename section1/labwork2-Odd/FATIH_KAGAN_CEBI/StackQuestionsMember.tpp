// StackQuestionsMember.tpp
// Contains Q1 and Q2 solutions

template <typename T>
T StackQuestions<T>::getKthFromTop(size_t k) const {
    if (k >= this->stack.size())
        throw std::out_of_range("k is out of range");

    Stack<T> temp = this->stack;
    for (size_t i = 0; i < k; i++) {
        temp.pop();
    }
    return temp.top();
}

template <typename T>
void StackQuestions<T>::sortStack() {
    Stack<T> temp;

    while (!this->stack.isEmpty()) {
        T val = this->stack.top();
        this->stack.pop();

        while (!temp.isEmpty() && temp.top() > val) {
            this->stack.push(temp.top());
            temp.pop();
        }

        temp.push(val);
    }

    while (!temp.isEmpty()) {
        this->stack.push(temp.top());
        temp.pop();
    }
}
