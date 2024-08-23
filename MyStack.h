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




#endif // MYSTACK_H
