//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_QUADLIST_H
#define DATASTRUCT_QUADLIST_H

#include "../list/list.h"
#include "quadlistnode.h"

template<typename T>
class quadlist {
public:
    typedef typename quadlistnode<T>::pointer node_pointer;

    quadlist():_size(0) { init(); }
    ~quadlist() { clear(); delete header; delete trailer; }

    int size() const { return _size; }
    bool empty() const { return _size < 1; }

    node_pointer first() { return header->succ; }
    node_pointer last() { return trailer->pred; }
    bool valid(node_pointer p) const { return p && p != header && p != trailer; }

    T remove(node_pointer);
    node_pointer insertAfterAbove(const T&e, node_pointer p, node_pointer x = nullptr); // 将e插入为p的后继，x的上邻
    int clear();

    void traverse(void(*)(T&));
protected:
    void init();
private:
    int _size;
    node_pointer header, trailer;
};

#endif //DATASTRUCT_QUADLIST_H
