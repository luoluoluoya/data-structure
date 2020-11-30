//
// Created by 张锐 on 2020/11/26.
//

#include "bintree.h"
#include <algorithm>


// todo 迭代替换
//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T>
static int removeAt (T x) {
    if (!x) return 0;
    int n = 1 + removeAt (x->lc) + removeAt (x->rc);
    delete x; return n;
}

template<typename T>
unsigned int bintree<T>::remove(node_pointer x) {
    if (x->hasParent())
        (x->isLc() ? x->parent->lc : x->parent->rc) = nullptr;
    updateHeightAbove(x->parent);
    return _size-=removeAt<node_pointer>(x);
}

template<typename T>
void bintree<T>::updateHeight(node_pointer p) {
    int hl = binTreeNodeHeight(p->lc);
    int hr = binTreeNodeHeight(p->rc);
    int m = std::max(hl, hr);
    p->height = 1 + m;
}

template<typename T>
typename bintree<T>::node_pointer bintree<T>::insertAsRoot(const T &e) {
    ++_size;
    return _root = new bintreenode<T>(e);
}

template<typename T>
typename bintree<T>::node_pointer bintree<T>::insertAsLc(node_pointer x, const T &e) {
    x->lc = new bintreenode(e, x);
    updateHeightAbove(x); ++_size;
    return x->lc;
}

template<typename T>
typename bintree<T>::node_pointer bintree<T>::insertAsRc(node_pointer x, const T &e) {
    x->rc = new bintreenode(e, x);
    updateHeightAbove(x); ++_size;
    return x->rc;
}

template<typename T>
typename bintree<T>::node_pointer bintree<T>::attachAsLc(node_pointer x, pointer t) {
    x->lc = t->_root; if (x->lc) x->lc->parent = x;
    updateHeightAbove(x); _size+=t->_size;
    t->_root = nullptr; t->_size = 0;
    return x->lc;
}

template<typename T>
typename bintree<T>::node_pointer bintree<T>::attachAsRc(node_pointer x, pointer t) {
    x->rc = t->_root; if (x->rc) x->rc->parent = x;
    updateHeightAbove(x); _size+=t->_size;
    t->_root = nullptr; t->_size = 0;
    return x->rc;
}

template<typename T>
typename bintree<T>::pointer bintree<T>::secede(node_pointer x) {
    if (x->hasParent()) {
        (x->isLc() ? x->parent->lc : x->parent->rc) = nullptr;  updateHeightAbove(x->parent);
    }
    pointer nt = new bintree<T>();
    nt->_root = x; nt->_size = x->childs(); nt->_root->parent = nullptr;
    _size-=nt->_size;
    return nt;
}