//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_LEFTHEAP_H
#define PLUS_LEFTHEAP_H

/**
 * 坐式堆
 * 问题：如何合并两个堆A，B； |A| = n，|B| = m；
 *  1. 完全二叉堆中， 将两个堆中的词条视作彼此独立的对象，从而可以直接借助Floyd算法，将它们组织为一个新的堆H； O(m+n);
 *  2. 反复取出堆B的最大词条并插入堆A中；当堆B为空时，堆A即为所需的堆H; O(mLog(n+m))
 *      while ( ! B.empty() )
 *          A.insert( B.delMax() );
 *  假设堆A，B完全无序时，构建堆的复杂度也为 O(m+n); 我们如何利用两个堆已有的偏序关系来提高堆的合并效率
 *
 *  堆是否也必须与二叉搜索树一样，尽可能地保持平衡？ 而不需要维护一个完全二叉树的结构？
 *  左式堆②（leftist heap）是优先级队列的另一实现方式，可高效地支持堆合并操作。其基本思路是：
 *      在保持堆序性的前提下附加新的条件，使得在堆的合并过程中，只需调整很少量的节点。具体地，需参与调整的节点不超过O(logn)个，故可达到极高的效率。
 *
 *  左式堆的倾斜度，应该控制在什么范围？又该如何控制？为此，可借鉴AVL树和红黑树的技巧，为各节点引入所谓的“空节点路径长度”指标，并依此确定相关算法的执行方向。
 *  节点x的空节点路径长度（null path length），记作npl(x)。若x为外部节点，则约定npl(x) = npl(null) = 0。反之若x为内部节点，则npl(x)可递归地定义为：
 *  npl(x) = 1 + min( npl(lc(x)), npl(rc(x)) )也就是说，节点x的npl值取决于其左、右孩子npl值中的小者。
 *
 *  npl(x)既等于x到外部节点的最近距离（该指标由此得名），同时也等于以x为根的最大满子树（图中以矩形框出）的高度。
 *
 * 左式堆是处处满足“左倾性”的二叉堆，即任一内部节点x都满足 npl(lc(x)) >= npl(rc(x))也就是说，就npl指标而言，任一内部节点的左孩子都不小于其右孩子。
 * 左式堆：左孩子的npl值不小二右孩子，而前者的高度却可能小于后者
 *
 * 左式堆中任一内节点x都应满足： npl(x) = 1 + npl(rc(x))  也就是说，左式堆中每个节点的npl值，仅取决于其右孩子
 *
 * 从x出发沿右侧分支一直前行直至空节点，经过的通路称作其最右侧通路（rightmost path），记作rPath(x)。在左式堆中，尽管右孩子高度可能大于左孩子，
 * 但由“各节点npl值均决定于其右孩子”这一事实不难发现，每个节点的npl值，应恰好等于其最右侧通路的长度。
 *
 * 最右侧通路的末节点 r 构成全树的最大满子树的最后节点。 故n个节点构成的二叉树， 其 rPath(r) <= log(n)
 *
 * 左式堆合并：
 *  设a堆顶大于b堆顶，可递归地将a的右子堆aR与堆b合并，然后作为节点a的右孩子替换原先的aR。当然，为保证依然满足左倾性条件，
 *  最后还需要比较a左、右孩子的npl值如有必要还需将二者交换，以保证左孩子的npl值不低于右孩子。
 *  复杂度：
 *      所有递归实例可排成一个线性序列。因此，该算法实质上属于线性递归，其运行时间应线性正比于递归深度。
 *      递归只可能发生于两个待合并堆的最右侧通路上。根据分析结论，若待合并堆的规模分别为n和m，则其两条最右侧通路的长度分别不会超过O(logn)和O(logm)，因此合并算法总体运行时间应不超过：
 *      O(logn) + O(logm) = O( logn + logm ) = O(log(max(n, m)))
 *
 *  堆的其他动态操作：
 *      insert：
 *          将插入元素独立成堆，并执行堆的合并；O(log(n))
 *      delMax：
 *          孤立堆顶，左右子树独立成堆并执行堆的合并；O(log(n))
 */

#include "priorityqueue.h"
#include "../bintree/bintree.h"
#include <cassert>
#include <algorithm>

#define binTreeNodeNpl(x)  ((x) ? (x)->npl : 0)
template<typename T>
class LeftHeap: public PriorityQueue<T>, protected bintree<T>{
public:
    typedef typename bintree<T>::node_pointer node_pointer;

    int size() const { return this->_size; }
    T getMax();

    void insert(const T&e);
    T delMax();

    void merge(LeftHeap<T> heap) {
        this->_root = merge(this->_root, heap._root); this->_size+=heap.size();
        heap._root = nullptr; heap._size = 0;
    }

protected:
    void updateNpl(node_pointer p) {
        p->npl = std::min( binTreeNodeNpl(p->lc), binTreeNodeNpl(p->rc) ) + 1;
    }
    void heapify(); //Floyd建堆算法
private:
    node_pointer merge(node_pointer a, node_pointer b);
};

#endif //PLUS_LEFTHEAP_H
