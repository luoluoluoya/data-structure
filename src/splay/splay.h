//
// Created by 张锐 on 2020/12/1.
//

#ifndef DATASTRUCT_SPLAY_H
#define DATASTRUCT_SPLAY_H

#include "../bst/bst.h"
#include <utility>

template<typename T>
class splay: public bst<T> {
public:
    typedef typename bintreenode<T>::pointer node_pointer;

    node_pointer &search(const T&e);
    virtual std::pair<node_pointer, bool> insert(const T&e);
    virtual bool remove(const T&e);
protected:
    node_pointer doSplay(node_pointer v);
};

#endif //DATASTRUCT_SPLAY_H
