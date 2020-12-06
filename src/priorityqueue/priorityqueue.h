//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_PRIORITYQUEUE_H
#define PLUS_PRIORITYQUEUE_H

template <typename T>
class PriorityQueue {
public:
    virtual int size() const = 0;
    virtual void insert(const T&e) = 0;
    virtual T delMax() = 0;
    virtual T getMax() = 0;
};

#endif //PLUS_PRIORITYQUEUE_H
