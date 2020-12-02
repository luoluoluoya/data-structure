//
// Created by 张锐 on 2020/12/1.
//

#include "splay.h"

//在节点*p与*lc（可能为空）之间建立父（左）子关系
template <typename T> inline
void attachAsLChild(typename splay<T>::node_pointer p, typename splay<T>::node_pointer lc) { p->lc = lc; if (lc) lc->parent = p; }

//在节点*p与*rc（可能为空）之间建立父（右）子关系
template <typename T> inline
void attachAsRChild(typename splay<T>::node_pointer p, typename splay<T>::node_pointer rc) { p->rc = rc; if (rc) rc->parent = p; }

// 双层伸展：伸展节点高度为偶数时可以直接伸展到_root, 奇数节点需要在使用一次zig/zag才可达到_root
template<typename T>
typename splay<T>::node_pointer splay<T>::doSplay(node_pointer v) {
    if (!v) return nullptr;
    node_pointer p, g;
    // 双层伸展
    while ((p = v->parent) && (g = p->parent)) {
        node_pointer gg = g->parent;
        if (p->isLc()) {
            if (v->isLc()) {    // ll
                attachAsLChild<T>(p, v->rc); attachAsLChild<T>(g, p->rc);
                attachAsRChild<T>(p, g); attachAsRChild<T>(v, p);
            } else {            // lr
                attachAsLChild<T>(g, v->rc); attachAsRChild<T>(p, v->lc);
                attachAsLChild<T>(v, p); attachAsRChild<T>(v, g);
            }
        } else {
            if (v->isRc()) {    // rr
                attachAsRChild<T>(g, p->lc); attachAsRChild<T>(p, v->lc);
                attachAsLChild<T>(p, g); attachAsLChild<T>(v, p);
            } else {            // rl
                attachAsLChild<T>(p, v->lc);attachAsRChild<T>(g,v->lc);
                attachAsLChild<T>(v, g); attachAsRChild<T>(v, p);
            }
        }
        v->parent = gg;
        if(gg)
            g == gg->lc ? attachAsLChild<T>(gg, v) : attachAsRChild<T>(gg, v);
        this->updateHeight(g); this->updateHeight(p); this->updateHeight(v);
    }
    if (p) {
        if (v == p->lc) {
            attachAsLChild<T>(p, v->rc); attachAsRChild<T>(v, p);
        } else {
            attachAsRChild<T>(p, v->lc); attachAsLChild<T>(v, p);
        }
        this->updateHeight(p); this->updateHeight(v);
    }
    v->parent = nullptr;
    return v;
}

template<typename T>
bool splay<T>::remove(const T &e) {
    if (!this->_root || search(e)->data != e)
        return false;
    node_pointer w = this->_root;
    if (!w->hasLc()) {
        this->_root = w->rc; if (this->_root) this->_root->parent = nullptr;
    } else if (!w->hasRc()) {
        this->_root = w->lc; if (this->_root) this->_root->parent = nullptr;
    } else {
        node_pointer lT = w->lc;  w->lc = nullptr; lT->parent = nullptr;        // 左侧子树隔离
        this->_root = w->rc; w->rc = nullptr; this->_root->parent = nullptr;    // 右侧子树隔离
        search(e);  // 后继节点放入跟节点(必定无左子节点)
        this->_root->lc = lT; lT->parent = this->_root;                         // 左子树接入
    }
    delete w; this->_size--;
    if (this->_root) this->updateHeight(this->_root);
    return true;
}

template<typename T>
std::pair<typename splay<T>::node_pointer, bool> splay<T>::insert(const T &e) {
    // 退化情况
    if (this->empty()) {
        this->_size++;
        return std::make_pair((this->_root = new bintreenode<T>(e)), true);
    }
    // 搜索， 不存在时插入
    if (search(e)->data == e)
        return std::make_pair(this->_root, false);

    //创建新节点。调整指针以完成局部重构: saerch搜索将e的直接前驱/直接后继放入跟节点。 通过将_root与e进行大小比较重新规划树结构
    this->_size++; node_pointer t = this->_root;
    if (t->data < e) {
        t->parent = this->_root = new bintreenode<T>(e, nullptr, t, t->rc);
        if (t->hasRc())
            t->rc->parent = this->_root;
        t->rc = nullptr;
    } else {
        t->parent = this->_root = new bintreenode<T>(e, nullptr, t->lc, t);
        if (t->hasLc())
            t->lc->parent = this->_root;
        t->lc = nullptr;
    }
    this->updateHeight(this->_root);
    return std::make_pair(this->_root, true);
}

template<typename T>
typename splay<T>::node_pointer &splay<T>::search(const T &e) {
    //将最后一个被访问的节点伸展至根
    node_pointer p = searchIn(this->_root, e, this->_hot = NULL);
    this->_root = doSplay(p ? p : this->_hot);
    return this->_root;
}


