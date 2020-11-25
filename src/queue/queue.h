//
// Created by 张锐 on 2020/11/25.
//

#ifndef DATASTRUCT_QUEUE_H
#define DATASTRUCT_QUEUE_H

#include "../list/list.h"

template<typename T>
class queue: protected list<T> {
public:
    using list<T>::size;
    using list<T>::empty;
    void enqueue(const T &);
    T dequeue();
    T& front();
};

#endif //DATASTRUCT_QUEUE_H
