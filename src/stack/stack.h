//
// Created by 张锐 on 2020/11/25.
//

#ifndef DATASTRUCT_STACK_H
#define DATASTRUCT_STACK_H

#include "../vector/vector.h"

template<typename T>
class stack: public vector<T> {
public:
    using vector<T>::empty;
    void push(const T&);
    T pop();
    T &top();
};


#endif //DATASTRUCT_STACK_H
