//
// Created by 张锐 on 2020/11/25.
//

#include "queue.h"

template<typename T>
T queue<T>::dequeue() {
    return list<T>::remove( list<T>::front() );
}

template<typename T>
void queue<T>::enqueue(const T &e) {
    list<T>::insertBack(e);
}

template<typename T>
T & queue<T>::front() {
    return list<T>::front()->data;
}
