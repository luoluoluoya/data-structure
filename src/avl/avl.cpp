//
// Created by 张锐 on 2020/11/30->
//

#include "avl.h"

template<typename T>
std::pair<typename bst<T>::node_pointer, bool> avl<T>::insert(const T &e) {
    node_pointer &p = bst<T>::search(e);
    if (p) return std::make_pair(p, false);
    p = new bintreenode<T>(e, bst<T>::_hot); bintree<T>::size()++;
    for (node_pointer g = bst<T>::_hot; g; g = g->parent) {
        if (!balanced(g)) {
            auto fp = bintree<T>::fromParentTo(g);
            fp = bst<T>::rotateAt( tallerChild( tallerChild(g) ) ); break;
        } else {
            bintree<T>::updateHeight(g);
        }
    }
    return std::make_pair(p, true);
}

template<typename T>
bool avl<T>::remove(const T &e) {
    node_pointer &p = search(e), w = p, succ;   // p 搜索得到的节点；w 实际执行移除的节点； succ， 被移除节点的后继节点
    if (!p) return false;
    if (!p->hasLc()) {
        succ = p = p->rc;
    } else if (!p->hasRc()) {
        succ = p = p->lc;
    } else {
        node_pointer w = p->succ();
        std::swap(p->data, w->data);
        node_pointer u = w->parent;
        ( ( u == p ) ? u->rc : u->lc ) = succ = w->rc; //隔离节点*w
    }
    bst<T>::_hot = w->parent;
    if (succ)
        succ->parent = bst<T>::_hot;
    delete w;
    bintree<T>::size()--;
    for (node_pointer g = bst<T>::_hot; g; g = p->parent) {
        if (!balanced(g))
            g = g->fromParent() = bst<T>::rotateAt( tallerChild( tallerChild(g) ) );
        bintree<T>::updateHeight(g);
    }
    return true;
}