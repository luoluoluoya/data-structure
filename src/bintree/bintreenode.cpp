//
// Created by 张锐 on 2020/11/26.
//

#include "bintreenode.h"
#include <random>
#include <cstddef>
#include "../queue/queue.h"
#include "../stack/stack.h"

template<typename T>
typename bintreenode<T>::pointer bintreenode<T>::insertAsLc(const T &e) {
    return lc = new bintreenode<T>(e, this);
}

template<typename T>
size_t bintreenode<T>::childs() {
    size_t lcs = (hasLc()) ? lc->childs() : 0;
    size_t rcs = (hasRc()) ? rc->childs() : 0;
    return lcs + rcs + 1;
}

template<typename T>
typename bintreenode<T>::pointer bintreenode<T>::insertAsRc(const T &e) {
    return rc = new bintreenode<T>(e, this);
}
template<typename T>
typename bintreenode<T>::pointer bintreenode<T>::succ() {
    pointer s = this;
    if (hasRc()) {
        s = rc;
        while ( s->hasLc() ) s = s->lc;
    } else {
        while ( s->isRc() ) s = s->parent;
        s = s->parent;
    }
    return s;
}

template <typename T> template <typename VST>
void bintreenode<T>::travelLevel(VST &visitor) {
    queue<pointer> q;
    q.enqueue(this);
    while (!q.empty()) {
        pointer p = q.dequeue();
        visitor(p->data);
        if (p->hasLc()) q.enqueue(p->lc);
        if (p->hasRc()) q.enqueue(p->rc);
    }
}

template <typename T> template <typename VST>
void bintreenode<T>::travelPre(VST &visitor) {
    int num = random() % 4;
    switch (num) {
        case 0: travelPre1(visitor); break;
//        case 1: travelPre2(visitor); break;  // todo stack error
        default: travelPre3(visitor); break;
    }
}

template <typename T> template <typename VST>
void bintreenode<T>::travelPre1(VST &visitor) { // 递归
    visitor(this->data);
    if (hasLc()) lc->travelPre1(visitor);
    if (hasRc()) rc->travelPre1(visitor);
}

//template <typename T> template <typename VST>
//void bintreenode<T>::travelPre2(VST &visitor) {
//    stack<pointer> s;
//    s.push(this);
//    while ( !s.empty() ) {
//        pointer p = s.pop();
//        while ( p->hasLc() ) {
//            visitor(p->data);
//            if (p->hasRc()) s.push(p->rc);
//            p = p->lc;
//        }
//    }
//}

template <typename T> template <typename VST>
void bintreenode<T>::travelPre3(VST &visitor) {
    pointer p = this;
    while (true) {
        p->status = visited;
        visitor(p->data);
        if (p->hasLc()) {
            p = p->lc;
        } else if(p->hasRc()) {
            p = p->rc;
        } else {
            while ( (p = p->parent) && ( !p->hasRc() || p->rc->status == visited ) );
            if (p) p = p->rc;
        }
        if (!p) break;
    }
}

template <typename T> template <typename VST>
void bintreenode<T>::travelIn(VST &visitor) {
    int num = random() % 4;
    switch (num) {
        case 0: travelIn1(visitor); break;
//        case 1: travelIn2(visitor); break;  // todo stack error
        case 2: travelIn3(visitor); break;
        default: travelIn4(visitor); break;
    }
}

template <typename T> template <typename VST>
void bintreenode<T>::travelIn1(VST &visitor) {
    if (this->hasLc()) lc->travelIn1(visitor);
    visitor(this->data);
    if (this->hasRc()) rc->travelIn1(visitor);
}

//template <typename T>
//inline void downToLeftmostPath(typename bintreenode<T>::pointer p, stack<typename bintreenode<T>::pointer> &stack) {
//    if (!p) return;
//    stack.push(p);
//    while ( p->hasLc() )
//        stack.push( (p = p->lc) );
//}

//template <typename T> template <typename VST>
//void bintreenode<T>::travelIn2(VST &visitor) {
//    stack<pointer> s;
//    pointer p = this;
//    do {
//        downToLeftmostPath<T>(p, s);
//        p = s.pop();
//        visitor(p->data);
//        p = p->rc;
//    } while ( !s.empty() );
//}

template <typename T> template <typename VST>
void bintreenode<T>::travelIn3(VST &visitor) {
    pointer p = this;
    while(true) {
        if ( p->hasLc() ) {
            p = p->lc;
        } else {
            visitor(p->data);
            while ( !p->hasRc() ) {
                if ( !(p = p->succ()) ) return;
                visitor(p->data);
            }
            p = p->rc;
        }
    }
}

template <typename T> template <typename VST>
void bintreenode<T>::travelIn4(VST &visitor) {
    bool backtrace = false;
    pointer p = this;
    while (true) {
        if ( !backtrace && p->hasLc() ) {   // 沿着最左侧路径深入
            p = p->lc;
        } else {                            // 无左子树or已回溯到当前节点（左子树访问完成）
            visitor(p->data);
            if (p->hasRc()) {
                p = p->rc; backtrace = false;
            } else {
                p = p->succ(); backtrace = true;
            }
        }
        if(!p) break;
    }
}

template<typename T> template<typename VST>
void bintreenode<T>::travelPost(VST &visitor) {
    int num = random() % 2;
    switch (num) {
        case 0: travelPost1(visitor); break;
//        case 1: travelPost2(visitor); break;  // todo stack error
        default: travelPost3(visitor); break;
    }
}

template<typename T> template<typename VST>
void bintreenode<T>::travelPost1(VST &visitor) {
    if (this->hasLc()) lc->travelPost1(visitor);
    if (this->hasRc()) rc->travelPost1(visitor);
    visitor(this->data);
}

//template <typename T>
//inline void HVF(typename bintreenode<T>::pointer p, stack<typename bintreenode<T>::pointer> &stack) {
//    if (!p) return;
//    stack.push(p);
//    while ( p->hasLc() ) {
//        stack.push( (p = p->lc) );
//    }
//}

//template<typename T> template<typename VST>
//void bintreenode<T>::travelPost2(VST &visitor) {
//    stack<pointer> s;
//    pointer p = this;
//    do {
//        while ( p ) {
//            s.push(p);
//            if (p->hasRc()) s.push(p->rc);
//            if (p->hasLc()) s.push(p->lc);
//            p = p->lc;
//        }
//        p = s.pop(); visitor(p->data);
//        p = p->isLc() ? s.pop() : p;    // 出栈节点不一定再执行上述算法
//    } while (!s.empty());
//}

template<typename T> template<typename VST>
void bintreenode<T>::travelPost3(VST &visitor) {
    pointer p = this, b = nullptr; bool backtrace = false;
    while(true) {
        if ( !backtrace && p->hasLc() ) {       // 沿最左侧路径深入
            p = p->lc;
        } else {
            visitor(p->data);                   // 到底时访问节点， 并对后继节点继续执行上诉算法；
            if ( (b = p->rightBrother()) ) {  // 右兄弟作为后继
                p = b; backtrace = false;   // 父节点作为后继
            } else {
                p = p->parent; backtrace = true;
            }
        }
        if (!p) break;
    }
}

// 对当前节点执行顺时针旋转： 让当前节点和 rc 的深度 -1； lc.rc 深度不变； lc和lc.lc节点深度 +1
template<typename T>
typename bintreenode<T>::pointer bintreenode<T>::zig() {
    pointer lChild = lc;
    lChild->parent = this->parent;
    if ( lChild->parent )
        ( ( this == lChild->parent->rc ) ? lChild->parent->rc : lChild->parent->lc ) = lChild;
    lc = lChild->rc; if ( lc ) lc->parent = this;
    lChild->rc = this; this->parent = lChild;
    return lChild;
}

// 对当前节点执行逆时针旋转: 当前节点的深度 -1； rc.lc 深度不变； rc和rc.rc深度 +1
template<typename T>
typename bintreenode<T>::pointer bintreenode<T>::zag() {
    pointer rChild = rc;
    rChild->parent = this->parent;
    if ( rChild->parent )
        ( ( this == rChild->parent->lc ) ? rChild->parent->lc : rChild->parent->rc ) = rChild;
    rc = rChild->lc; if ( rc ) rc->parent = this;
    rChild->lc = this; this->parent = rChild;
    return rChild;
}