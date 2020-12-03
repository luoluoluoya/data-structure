//
// Created by 张锐 on 2020/12/3.
//

#include "redblack.h"

template<typename T>
std::pair<typename redblack<T>::node_pointer, bool> redblack<T>::insert(const T &e) {
    node_pointer& x = this->search (e);
    if (x) return std::make_pair(x, false);
    x = new bintreenode<T>(e, this->_hot, nullptr, nullptr, 0); this->_size++;
    solveDoubleRed (x); return x ? std::make_pair(x, true) : std::make_pair(this->_hot->parent, false);
}

template<typename T>
bool redblack<T>::remove(const T &e) {
    node_pointer &x = this->search(e);
    if (!x) return false;
    node_pointer r = removeAt<T>(x, this->_hot);
    if (! (--this->_size)) return true;
    if (! this->_hot) {
        this->_hot->color = bintreenode<T>::black; this->updateHeight (this->_root);
        return true;
    }
    if (blackHeightUpdated(this->_hot))
        return true;
    if (isRed(r)) {
        r->color = bintreenode<T>::black; r->height++;
        return true;
    }
    solveDoubleBlack (r); return true;
}

template<typename T>
void redblack<T>::solveDoubleRed(node_pointer x) {
    // 已调整到树根，高度增加
    if (this->isRoot(x)) {
        x->color = bintreenode<T>::black; x->height++;
        return;
    }
    node_pointer p = x->parent;
    // 双红终止
    if (isBlack(p)) return;
    // g 必定存在且为黑
    node_pointer g = p->parent, u = x->uncle();

    if(isRed(u)) { // 节点溢出
        g->color = bintreenode<T>::red;
        p->color = bintreenode<T>::black; p->height++;
        u->color = bintreenode<T>::black; p->height++;
        solveDoubleRed(g);
    } else {       // 节点存在相邻红色
        // 同侧时p居中，不同侧时v居中
        if (p->isLc() == x->isLc())
            p->color = bintreenode<T>::black;
        else
            x->color = bintreenode<T>::black;
        g->color = bintreenode<T>::red;
        node_pointer gg = g->parent;
        node_pointer r = this->fromParentTo(g) = this->rotateAt(x);
        r->parent = gg;
    }
}

template<typename T>
void redblack<T>::solveDoubleBlack(node_pointer x) {
    node_pointer p = x ? x->parent : this->_hot;
    if (!p) return;
    node_pointer s = (x == p->lc) ? p->rc : p->lc;
    if (isBlack(s)) {   // 黑兄弟
        node_pointer t = nullptr;
        if (isRed(s->rc)) t = s->rc;
        if (isRed(s->lc)) t = s->lc;
        // 黑兄弟是否存在红子节点
        if (t) {
            auto oldColor = p->color;
            node_pointer r = this->fromParentTo(p) = this->rotateAt(t);
            if (r->hasLc()) { r->lc->color = bintreenode<T>::black; updateHeight(r->lc); }
            if (r->hasRc()) { r->rc->color = bintreenode<T>::black; updateHeight(r->rc); }
            r->color = oldColor; updateHeight(r);
        } else {
            s->color = bintreenode<T>::red; s->height--;
            // 不存在红子节点时考察父节点是否为红节点
            if (isRed(p)) {
                p->color = bintreenode<T>::black;
            } else {
                p->height--;
                solveDoubleBlack(p);
            }
        }
    } else {   // 红兄弟
        node_pointer t = s->isLc() ? s->lc : s->rc;  // tsp || pst
        s->color = bintreenode<T>::black; p->color = bintreenode<T>::red;
        this->_hot = p;
        this->fromParentTo(p) = this->rotateAt(t);
        solveDoubleBlack(x);
    }
}
