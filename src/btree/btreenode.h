//
// Created by 张锐 on 2020/12/2.
//

#ifndef DATASTRUCT_BTREENODE_H
#define DATASTRUCT_BTREENODE_H

#include "../vector/vector.h"

template<typename T>
struct btreenode {
    typedef btreenode<T>* pointer;
    typedef btreenode<T>& reference;

    btreenode():parent(nullptr) { childs.insert(nullptr); }

    btreenode(const T&e, pointer lc = nullptr, pointer rc = nullptr):parent(nullptr) {
        keys.insert(e);
        childs.insert(lc); childs.insert(rc);
    }

    vector<T> keys;
    vector<pointer> childs;
    pointer parent;
};

#endif //DATASTRUCT_BTREENODE_H
