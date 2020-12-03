//
// Created by 张锐 on 2020/12/2.
//

#ifndef DATASTRUCT_BTREE_H
#define DATASTRUCT_BTREE_H

#include "btreenode.h"
#include <utility>


/*
算法细节描述：
    m阶b树：
        子节点数： [ ceil(m/2), m ]
        关键字数： [ ceil(m/2) - 1, m-1 ]
        eg： 红黑树（4阶b树） [ 2, 4 ], [1, 3]
    节点下溢：
        节点中关键字被移除时导致当前节点的关键字数等于 ceil(m/2)-2
        修复：
            1. 左顾右盼：通过父节点从节点充裕的兄弟节点中转借节点（左顾/右盼）；
                关键字数量合法性不言而喻
            2. 合并：通过父节点链接并合并某个兄弟节点（左合并/右合并）；
                ceil(m/2)-2 + ceil(m/2)-1 + 1 = 2*ceil(m/2)-2 <= m-1
    节点上溢：
        节点中关键字新增时导致当前节点的关键字数等于 m
        修复：
            1. 分裂：选取当前节点关键字中间元素插入如节点适当位置， 并将当前节点据此进行分裂为两个节点并分据为 lc， rc
                (m-1)/2

    vector的 search 方法返回不大于当前搜索元素 e 的最大位置 r； _ele[r] <= e; 故若 _ele[r] != e 时，insert(r+1, e);
 */
template<typename T>
class btree {
public:
    typedef typename btreenode<T>::pointer node_pointer;
    typedef typename btreenode<T>::reference node_reference;
    typedef unsigned int size_type;

    btree(size_type o = 4):_order(o),_size(0),_root(new btreenode<T>()),_hot(nullptr) {}
    ~btree() { _hot = nullptr; clear(_root); }

    size_type& size() { return _size; }
    node_pointer& root() { return _root; }
    size_type order() const { return _order; }
    bool empty() const { return !_size; }

    std::pair<node_pointer, bool> insert(const T&e);
    bool remove(const T&e);
    node_pointer search(const T&e);

protected:
    // 节点上溢修复
    void solveOverflow(node_pointer);
    // 节点下溢修复
    void solveUnderflow(node_pointer);
    void clear(node_pointer);
private:
    size_type _size;
    size_type _order;
    node_pointer _root;
    node_pointer _hot;
};

#endif //DATASTRUCT_BTREE_H
