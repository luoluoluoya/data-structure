//
// Created by 张锐 on 2020/11/30.
//

#ifndef DATASTRUCT_AVL_H
#define DATASTRUCT_AVL_H

#include "../bst/bst.h"
#include <utility>

template<typename T>
class avl: public bst<T>{
public:
    typedef typename bst<T>::node_pointer node_pointer;
    std::pair<node_pointer, bool> insert(const T&e);
    bool remove(const T&e);
protected:
    // 给定节点是否平衡
    bool balanced(node_pointer p) const {
        int f = binTreeNodeHeight(p->lc) - binTreeNodeHeight(p->rc);
        return -2 < f && f < 2;
    }
    node_pointer tallerChild(node_pointer p) {
        auto q = p->higherChildNode();
        return q;
    }
};


#endif //DATASTRUCT_AVL_H
