//
// Created by 张锐 on 2020/11/30.
//

#include "bst.h"


template<typename T>
typename bst<T>::node_pointer &bst<T>::search(const T &e) {
    return searchIn(this->root(), e, _hot = NULL);
}

//在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e, 节点v（或假想的通配哨兵）的关键码等于e
#define EQUAL(e, v)  (!(v) || (e) == (v)->data)
template <typename T>
static typename bst<T>::node_pointer& searchIn(typename bst<T>::node_pointer&v, const T& e, typename bst<T>::node_pointer& hot) {
    if (EQUAL (e, v)) return v; hot = v;
    while (1) {
        typename bst<T>::node_pointer& c = (e < hot->data) ? hot->lc : hot->rc;
        if (EQUAL (e, c))
            return c;
        hot = c;
    }
}

template<typename T>
std::pair<typename bst<T>::node_pointer, bool> bst<T>::insert(const T &e) {
    node_pointer &p = search(e);
    if (p) return std::make_pair(p, false);
    p = new bintreenode<T>(e, _hot);
    this->size()++;
    this->updateHeightAbove(_hot);
    return std::make_pair(p, true);
}

// BST节点删除算法：删除位置x所指的节点。目标x在此前经查找定位，并确认非NULL，故必删除成功；与searchIn不同，调用之前不必将hot置空。 返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲——二者均有可能是NULL
template <typename T>
static typename bst<T>::node_pointer removeAt(typename bst<T>::node_pointer& x, typename bst<T>::node_pointer& hot) {
    typename bst<T>::node_pointer w = x, succ = nullptr; //实际被摘除的节点，初值同x; succ 实际被删除节点的接替者
    if (!x->hasLc())
        succ = x = x->rc;
    else if (!x->hasRc())
        succ = x = x->lc;
    else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要（在右子树中）找到*x的直接后继*w. 交换*x和*w的数据元素, 隔离节点*w
        w = w->succ();
        std::swap (x->data, w->data);
        typename bst<T>::node_pointer u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc;
    }
    //记录实际被删除节点的父亲, 并将被删除节点的接替者与hot相联
    hot = w->parent;
    if (succ) succ->parent = hot;
    delete w;
    return succ;
}


template<typename T>
bool bst<T>::remove(const T &e) {
    node_pointer &x = search (e);
    if (!x)
        return false;
    removeAt<T>(x, _hot); this->_size--;
    this->updateHeightAbove (_hot);
    return true;
}

template<typename T>
typename bst<T>::node_pointer bst<T>::connection34(node_pointer a, node_pointer b, node_pointer c, node_pointer t0, node_pointer t1, node_pointer t2, node_pointer t3) {
    a->lc = t0; if (t0) t0->parent = a;
    a->rc = t1; if (t1) t1->parent = a; this->updateHeight (a);
    c->lc = t2; if (t2) t2->parent = c;
    c->rc = t3; if (t3) t3->parent = c; this->updateHeight (c);
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; this->updateHeight (b);
    return b;
}

// 旋转节点恢复平衡
template<typename T>
typename bst<T>::node_pointer bst<T>::rotateAt(node_pointer v) { // v为更高的孙子节点
    node_pointer p = v->parent, g = p->parent;
    if (p->isLc()) {
        if (v->isLc()) {    // ll   =>  g->zig()   (zig顺时针旋转,zag逆时针旋转)
            p->parent = g->parent;
            return connection34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {            // lr   =>  v->zag() && p->zig()
            v->parent = g->parent;
            return connection34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {
        if (v->isRc()) {    // rr   => g->zag()
            p->parent = g->parent;
            return connection34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {            // rl   => v->zig() && p->zag()
            v->parent = g->parent;
            return connection34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

// 旋转节点恢复平衡
template<typename T>
typename bst<T>::node_pointer bst<T>::rotateReBalance(node_pointer v) {
    node_pointer p = v->parent, g = p->parent, s;
    if (p->isLc()) {
        if (v->isLc()) {    // ll   =>  g->zig()   (zig顺时针旋转,zag逆时针旋转)
            s = g->zig();
        } else {            // lr   =>  v->zag() && p->zig()
            v->zag(); s = g->zig();
        }
    } else {
        if (v->isRc()) {    // rr   => g->zag()
            s = p->zag();
        } else {            // rl   => v->zig() && p->zag()
            v->zig(); s = g->zag();
        }
    }
    return s;
}
