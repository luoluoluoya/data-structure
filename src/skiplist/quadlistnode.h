//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_QUADLISTNODE_H
#define DATASTRUCT_QUADLISTNODE_H

template<typename T>
struct quadlistnode {
    T entry;
    typedef quadlistnode* pointer;

    pointer pred, succ, blow, above;    // 前驱，后继，下邻，上邻

    quadlistnode(const T&e = T(), pointer p = nullptr, pointer s = nullptr, pointer b = nullptr, pointer a = nullptr):entry(e),pred(p),succ(s),blow(b),above(a) {}

    // 将e插入为当前节点的后继， x节点的上邻/x无上邻
    pointer insertAsSuccAbove(const T&e, pointer x = nullptr) {
        pointer np = new quadlistnode<T>(e, this, this->succ, x);
        succ->pred = np;  succ = np;
        if (x) x->above = np;
        return np;
    }
};

#endif //DATASTRUCT_QUADLISTNODE_H
