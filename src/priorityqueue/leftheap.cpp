//
// Created by 47302 on 2020/12/6.
//

#include "leftheap.h"

template<typename T>
void LeftHeap<T>::insert(const T &e) {
    node_pointer np = new bintreenode<T>(e);
    this->_root = merge(this->_root, np);
    this->_size++;
}

template<typename T>
T LeftHeap<T>::delMax() {
    // 隔离根节点
    node_pointer l = this->_root->lc, r = this->_root->rc;
    this->_root->lc = this->_root->rc = nullptr;
    //保存数据并移除
    T e = this->_root->data;
    delete this->_root; --this->_size;
    // 更新根节点
    this->_root = merge(l, r); if (this->_root) this->_root->parent = nullptr;
    return e;
}

template<typename T>
typename LeftHeap<T>::node_pointer LeftHeap<T>::merge(node_pointer a, node_pointer b) {
    //退化情况
    if (!a) return b;
    if (!b) return a;
    if (a->data < b->data) std::swap (a, b);
    a->rc = merge (a->rc, b);
    a->rc->parent = a;
    //若有必要。交换a的左、右子堆，以确保右子堆的npl不大
    if (!a->lc || a->lc->npl < a->rc->npl)
        std::swap(a->lc, a->rc);
    a->npl = a->rc ? a->rc->npl + 1 : 1;
    return a;
}

template<typename T>
T LeftHeap<T>::getMax() {
    assert(size() > 0);
    return this->_root->data;
}
