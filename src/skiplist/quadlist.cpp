//
// Created by 张锐 on 2020/12/3.
//

#include "quadlist.h"

template<typename T>
T quadlist<T>::remove(node_pointer p) {
    T e = p->entry;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    if (p->blow) p->blow->above = p->above;
    if (p->above) p->above->blow = p->blow;
    --_size;
    delete p;
    return e;
}

template<typename T>
typename quadlist<T>::node_pointer quadlist<T>::insertAfterAbove(const T &e, node_pointer p, node_pointer x) {
    _size++;
    return p->insertAsSuccAbove(e, x);
}

template<typename T>
void quadlist<T>::traverse(void (*visitor)(T &e)) {
    for (node_pointer p = first(); p != trailer; p = p->succ)
        visitor(p->entry);
}

template<typename T>
void quadlist<T>::init() {
    header = new quadlistnode<T>(); trailer = new quadlistnode<T>();
    header->succ = trailer; trailer->pred = header;
}

template<typename T>
int quadlist<T>::clear() {
    int s = _size;
    while (!empty())
        remove(first());
    return s;
}
