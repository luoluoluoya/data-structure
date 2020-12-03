//
// Created by 张锐 on 2020/12/2.
//

#include "btree.h"

template<typename T>
std::pair<typename btree<T>::node_pointer, bool> btree<T>::insert(const T &e) {
    node_pointer x = search(e);
    if (x) return std::make_pair(x, false);
    x = _hot;
    int r = x->keys.search(e);
    ++_size;
    x->keys.insert(r+1, e);
    x->childs.insert(r+2, nullptr);
    solveOverflow(x);
    return std::make_pair(x, true);
}

template<typename T>
bool btree<T>::remove(const T &e) {
    node_pointer x = search(e);
    if (!x) return false;
    int r = x->keys.search(e);
    // 若x非叶子，则e的后继必属于某叶节点,在右子树中一直向左，即可找出e的后继并与之交换位置,至此，x必然位于最底层，且其中第r个关键码就是待删除者
    if (x->childs[0]) {
        node_pointer succ = x->childs[r+1];
        while (succ->childs[0]) succ = succ->childs[0];
        std::swap(x->keys[r], succ->keys[0]); x = succ; _hot = succ->parent; r = 0;
    }
    x->keys.remove(r); x->childs.remove(r+1);
    --_size;
    solveUnderflow(x);
    return true;
}

template<typename T>
typename btree<T>::node_pointer btree<T>::search(const T &e) {
    node_pointer p = _root; _hot = nullptr;
    while (p) {
        int r = p->keys.search(e);
        if ( 0 <= r && p->keys[r] == e) break;
        _hot = p;
        p = p->childs[r+1];
    }
    return p;
}

template<typename T>
void btree<T>::solveOverflow(node_pointer x) {
    // 未上溢
    if (_order > x->keys.size())
        return;

    // 拆分当前节点: 移动子节点和关键字指针
    int mid = _order >> 1;
    node_pointer rc = new btreenode<T>();
    for (int i = 0; i < _order - mid - 1; ++i) {
        rc->keys.insert( i, x->keys.remove(mid+1) );
        rc->childs.insert( i, x->childs.remove(mid+1) ); if(rc->childs[i]) rc->childs[i]->parent = rc;
    }
    rc->childs[rc->childs.size()-1] = x->childs.remove(x->childs.size()-1); if( rc->childs[rc->childs.size()-1] ) rc->childs[rc->childs.size()-1]->parent = rc;  // _order - mid - 1

    // 获取父节点。当前节点为跟节点时，创建新跟节点并链接
    node_pointer p = x->parent;
    if (!p) {
        _root = x->parent = p = new btreenode<T>();
        _root->childs[0] = x;
    }
    // 中位数插入父节点并关联新子节点
    int r = p->keys.search(x->keys[0]);
    p->keys.insert( r+1, x->keys.remove(mid) );
    p->childs.insert(r+2, rc); rc->parent = p;

    solveOverflow(p);
}

template<typename T>
void btree<T>::solveUnderflow(node_pointer x) {
    // 未下溢
    if ( (_order+1)/2 <= x->childs.size() )
        return ;
    node_pointer p = x->parent;
    // 根节点平凡情况
    if (!p) {
        // 倘若作为树根的x已不含关键码，却有（唯一的）非空孩子，则这个节点可被跳过,并因不再有用而被销毁,整树高度降低一层
        if ( !x->keys.size() && x->childs[0] ) {
            _root = x->childs[0]; _root->parent = nullptr;
            x->childs[0] = nullptr; delete x;
            return;
        }
    }

    // 非根节点：转借，合并
    int r = 0; while (p->childs[r] != x) r++;
    // 与左子节点转借
    if (0 < r) {
        node_pointer lc = p->childs[r-1];
        if ( (_order+1)/2 < lc->childs.size() ) {
            x->keys.insert(0, p->keys[r-1]);
            p->keys[r-1] = lc->keys.remove( lc->keys.size() - 1 );
            x->childs.insert(0, lc->childs.remove( lc->childs.size() - 1 ));
            if (x->childs[0]) x->childs[0]->parent = x;
            return;
        }
    }
    // 与右子节点转借
    if ( r < _order - 1) {
        node_pointer rc = p->childs[r+1];
        if ( (_order+1)/2 < rc->childs.size() ) {
            x->keys.insert(p->keys[r]);
            p->keys[r] = rc->keys.remove(0);
            x->childs.insert(rc->childs.remove(0));
            if (x->childs[x->childs.size()-1]) x->childs[x->childs.size() -1]->parent = x;
            return;
        }
    }
    // 合并
    if (0 < r) {    // 与左子节点合并
        node_pointer lc = p->childs[r-1];
        lc->keys.insert(p->keys.remove(r-1)); p->childs.remove(r);
        lc->childs.insert( x->childs.remove(0) ); if (lc->childs[lc->childs.size()-1]) lc->childs[lc->childs.size()-1]->parent = lc;
        while (!x->keys.empty()) {
            lc->keys.insert( x->keys.remove(0) );
            lc->childs.insert( x->childs.remove(0) ); if (lc->childs[lc->childs.size()-1]) lc->childs[lc->childs.size()-1]->parent = lc;
        }
        delete x;
    } else {        // 与右子节点合并
        node_pointer rc = p->childs[r+1];
        rc->keys.insert(0, p->keys.remove(r)); p->childs.remove(r);
        rc->childs.insert(0, x->childs.remove(x->childs.size() -1) ); if (rc->childs[0]) rc->childs[0]->parent = rc;
        while (!x->keys.empty()) {
            rc->keys.insert(0, x->keys.remove(x->keys.size()-1));
            rc->childs.insert(0, x->childs.remove(x->childs.size()-1)); if (rc->childs[0]) rc->childs[0]->parent = rc;
        }
        delete x;
    }
    solveUnderflow(p);
}

template<typename T>
void btree<T>::clear(node_pointer x) {
    if (!x) return;
    for (int i = 0; i < x->childs.size(); ++i) {
        if (x) clear(x->childs[i]);
    }
    delete x;
}
