//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_COMPLETE_BINARY_HEAP_H
#define PLUS_COMPLETE_BINARY_HEAP_H

#include "priorityqueue.h"
#include "../vector/vector.h"



/**
 * 基于完全二叉树构造的优先级队列
 * 堆：堆序性 + 结构性
 *    堆序性：最大/最小元素（某一优先级属性为序）总维持在堆结构的最顶部
 *    结构性： 此处以完全二叉树为结构
 * 对完全二叉树的层序遍历从0到n进行排序时得到的元素序列和vector的元素秩刚好符合。 故可用vector来实现堆的`结构性`
 * 秩r为非根且存在左右子节点的内部节点 ：
 *      lc = 2i + 1; rc = 2i+2; parent = (i-1) >> 1
 * 动态操作对堆序性的影响：
 *      insert：插入元素到末尾
 *          插入元素不一定小于其父节点；
 *          上滤修复： 将当前节点与其父节点进行比较和交换， 直至其不大于父节点
 *          复杂度：每次比较和交换不过常数，交换之后失衡位置上升一层， 累计不过完全二叉树的高度 O(lgn)
 *      delMax：将堆顶与末尾元素互换后删除末尾元素
 *          新堆顶元素小于其左右子节点；
 *          下滤修复： 将当前节点与其左右子节点的较大者进行比较和交换， 直至其大于左右子节点或达到叶节点
 *          复杂度：每次比较和交换不过常数，交换之后失衡位置下降一层， 累计不过完全二叉树的高度 O(lgn)
 *  建堆操作：
 *      1. for i = 0 to n-1: insert(A[i]); 逐次插入元素建堆；
 *          复杂度：O(nlgn)
 *          O(nlgn) 的时间足够维护序列的一个全序关系，此处确只维护了一个偏序关系
 *          分析：
 *              考虑节点 r 插入时的情况， 其深度为 log(r)， 插入后的上滤修复复杂度为 log(r), 线性正比于节点所处的深度;
 *              在一个完全二叉堆中，节点的深度越深，元素个数越多。
 *          优化策略：
 *              让节点插入时的修复复杂度线性正比于节点所处的高度（高度越低，元素越多）
 *      2. for i = parent(n) to 0: underRepair(i);
 *          从最后一个内部节点开始执行下滤修复；
 */

#include <algorithm>
#include <cassert>

template<typename T>
class CompleteBinaryHeap: public PriorityQueue<T> {
public:
    CompleteBinaryHeap():_elem(vector<T>()) {}
    CompleteBinaryHeap(T elements[], int size);
    CompleteBinaryHeap(vector<T> elements):_elem(elements) { heapify(); }
    int size() const { return _elem.size(); }
    void insert(const T&e) { upRepair(_elem.insert(e)); }
    T delMax();
    T getMax() { return _elem[0]; }
protected:
    void upRepair(int r);       // 上滤修复
    void downRepair(int r);     // 下滤修复
    bool valid(int r) { return 0 <= r && r < _elem.size(); }
    int parent(int r) { return (r-1)/2; }
    int lChild(int r) { return r*2+1; }
    int rChild(int r) { return r*2+2; }
    int larger(int a, int b) { return _elem[a] < _elem[b] ? b : a; }    // 相等时优先返回a
    int largerLcAndRc(int r) {
        int lc = lChild(r); int rc = rChild(r);
//        printf("rank: %d %d \t", r, _elem[r]);
//        printf("lc: %d %d \t", lc, valid(lc) ? _elem[lc] : -1);
//        printf("rc: %d %d\t", rc, valid(rc) ? _elem[rc] : -1);
        auto lar = valid(lc) ? ( valid(rc) ? ( larger(r, larger(lc, rc)) ) : larger(r, lc) ) : ( valid(rc) ? larger(r, rc) : r );
//        printf("larger: %d %d\n", lar, _elem[lar]);
        return lar;
    }
    void heapify(); //Floyd建堆算法
private:
    vector<T> _elem;
};

#endif //PLUS_COMPLETE_BINARY_HEAP_H
