#ifndef MYSTACK_H
#define MYSTACK_H

#include <vector>
#include <stdexcept>

template<typename T>
class MYSTACK {
public:
    int size() const;
    void push(const T& element);
    void pop();
    T& top();
    bool empty() const;

private:
    std::vector<T> order;
};


template<typename T>
int MYSTACK<T>::size() const {
    return order.size();
}

template<typename T>
void MYSTACK<T>::push(const T& element) {
    order.push_back(element);
}

template<typename T>
void MYSTACK<T>::pop() {
    if (order.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    order.pop_back();
}

template<typename T>
T& MYSTACK<T>::top() {
    if (order.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return order.back();
}

template<typename T>
bool MYSTACK<T>::empty() const {
    return order.empty();
}

#endif // MYSTACK_H
