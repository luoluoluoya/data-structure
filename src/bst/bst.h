//
// Created by 张锐 on 2020/11/30.
//

#ifndef DATASTRUCT_BST_H
#define DATASTRUCT_BST_H

#include "../bintree/bintree.h"
#include <utility>

template<typename T>
class bst : public bintree<T> {
public:
    typedef bintree<T>* pointer;
    typedef typename bintreenode<T>::pointer node_pointer;

    node_pointer &search(const T&e);
    virtual std::pair<node_pointer, bool> insert(const T&e);
    bool remove(const T&e);
protected:
    node_pointer connection34(node_pointer a, node_pointer b, node_pointer c, node_pointer t0, node_pointer t1, node_pointer t2, node_pointer t3);  // 3 + 4 调整树局部结构
    node_pointer rotateReBalance(node_pointer v);
    node_pointer rotateAt(node_pointer v);

    node_pointer _hot;
};

#endif //DATASTRUCT_BST_H