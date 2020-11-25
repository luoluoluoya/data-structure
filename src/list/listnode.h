//
// Created by 张锐 on 2020/11/25.
//

#ifndef DATASTRUCT_LISTNODE_H
#define DATASTRUCT_LISTNODE_H

template<typename T>
class listnode {
public:
    typedef listnode<T>* pointer;
    typedef const listnode<T>* const_pointer;

    T data;
    pointer pred;
    pointer succ;

    listnode()=default;
    listnode(const T&e, pointer p = nullptr, pointer s = nullptr): data(e), pred(p), succ(s) {}

    // 修改器
    pointer insertAsAfter(const T &e);
    pointer insertAsBefore(const T &e);
};

#endif //DATASTRUCT_LISTNODE_H
