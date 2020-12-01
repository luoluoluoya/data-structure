//
// Created by 张锐 on 2020/11/30->
//

#include "avl.h"

template<typename T>
std::pair<typename bst<T>::node_pointer, bool> avl<T>::insert(const T &e) {
    node_pointer &p = this->search(e);
    if (p) return std::make_pair(p, false);
    p = new bintreenode<T>(e, this->_hot); this->size()++;
    for (node_pointer g = this->_hot; g; g = g->parent) {
        if (!balanced(g)) {
            node_pointer &fp = this->fromParentTo(g);
            fp = this->rotateAt(tallerChild(tallerChild(g))); break;
        } else {
            this->updateHeight(g);
        }
    }
    return std::make_pair(p, true);
}

template<typename T>
bool avl<T>::remove(const T &e) {
    node_pointer &x = this->search (e);
    if (!x)
        return false;
    removeAt<T>(x, this->_hot); this->_size--;
    //从_hot出发向上，逐层检查各代祖先g, 一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至原父亲.并更新其高度（注意：即便g未失衡，高度亦可能降低）; 可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
    for (node_pointer g = this->_hot; g; g = g->parent) {
        if (!balanced(g))
            g = this->fromParentTo(g) = this->rotateAt(tallerChild (tallerChild (g)));
        this->updateHeight (g);
    }
    return true;
}