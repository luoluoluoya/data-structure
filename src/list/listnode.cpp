//
// Created by 张锐 on 2020/11/25.
//

#include "listnode.h"

template<typename T>
typename listnode<T>::pointer listnode<T>::insertAsAfter(const T &e) {
    pointer n = new listnode<T>(e, this, succ);
    succ->pred = n; succ = n;
    return n;
}

template<typename T>
typename listnode<T>::pointer listnode<T>::insertAsBefore(const T &e) {
    pointer n = new listnode<T>(e, pred, this);
    pred->succ = n; pred = n;
    return n;
}


