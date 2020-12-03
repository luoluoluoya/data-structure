//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_REDBLACK_H
#define DATASTRUCT_REDBLACK_H

#include "../bst/bst.h"
#include <algorithm>


/*
====================================================================
红黑树：
    1.每个结点要么是红的要么是黑的。
    2.根结点是黑的。
    3.每个叶结点（也节点+哨兵节点）都是黑的。
    4.如果一个结点是红的，那么它的两个儿子都是黑的。
    5.对于任意结点而言，其到叶结点的每条路径都包含相同数目的黑结点。
====================================================================
动态操作对红黑树性质的影响：
插入
    插入节点设置为红(避免黑高度直接增加)； 当父节点为红色时出现`双红问题`
移除
    当移除点为红色时直接执行。移除节点为黑色且子节点为黑色时，到达当前子节点的黑高度降低。出现`双黑问题`
====================================================================
红黑树与B树
    红黑树中红节点上浮到黑色父节点的左/右侧形成超级节点时：
        超级节点可能具有 1～3个元素。
        黑节点必定居中，红节点分布两侧
        超级节点含有 [2,4] 个分支
    变换的红黑树与4阶B树等价

超级节点的颜色转换
    超级节点内红黑转换可能包含拓扑结构的转换
====================================================================
插入节点 v， v父节点 p， v 兄弟 u
双红修复: v == red && p == red
    1. u = red  : （4阶B树的上溢）
        4阶B树修复：以居中关键字 p 进行超级节点进行拆分，并将p放入父节点，拆分后节点接入p左/右子节点； 递归修复（p）
        红黑树修复：p 更改为红色，u和v更改为黑色； 递归修复（p）
    2. u != red : （4阶B树未上溢，黑色节点未居中）
        红黑树修复：重染色使黑色节点居中（跟随拓扑结构的变化）； 立即修复
====================================================================
移除节点 v， 移除节点子节点 r, 移除节点父节点 p， 移除节点兄弟 u, 移除节点祖父节点 gg
双黑修复
    1. u = black：
        a. u存在红子节点： （4阶B树的`胖兄弟`节点）
            4阶B树修复：通过父节点p转借兄弟节点的一个关键字使自身恢复平衡； 立即修复
            红黑树修复：对p执行顺/逆时针旋转， p更改为黑色，p位置替换者更换为p以前的颜色，u位置替代者变为黑色； 立即修复
        b. u不存在红子节点： （4阶B树的`瘦兄弟`节点）
            I.  p=red :
                4阶B树修复：通过父节点合并节点数即将下溢的兄弟节点成为新的超级节点； 立即修复（p）
                红黑树修复：p变为黑色，u，v更改为红色； 立即修复（p）
            II. p!=red:
                4阶B树修复：通过父节点合并节点数即将下溢的兄弟节点成为新的超级节点；递归修复（p）
                红黑树修复：节点s由黑转红； 递归修复（p）
    2. u = red：
        红黑树修复：交换p，u颜色（p变红，u变黑）。此时伴随拓扑结构的转换，转换之后的待移除节点v具有黑色兄弟节点，红色父节点;  转化为可立即修复的情况
====================================================================
 */
template<typename T>
class redblack: public bst<T> {
public:
    typedef typename bintreenode<T>::pointer node_pointer;

    std::pair<node_pointer, bool> insert(const T&e);
    bool remove(const T&e);

protected:
    void updateHeight(node_pointer p) {
        int m = std::max(binTreeNodeHeight(p->lc), binTreeNodeHeight(p->rc));
        p->height = isBlack(p) ? m+1 : m;
    }
    bool isRed(node_pointer p) const  { return !isBlack(p); }
    bool isBlack(node_pointer p) const  { return !p || p->color == bintreenode<T>::red; }

    // 黑高度是否更新： 1. 黑节点的黑高度不等于子节点+1； 2. 红节点的黑高度不等于子节点； 3.左右子节点黑高度不等
    bool blackHeightUpdated(node_pointer p) const  {
        return binTreeNodeHeight(p->lc) == binTreeNodeHeight(p->rc)
            && (isBlack(p) && binTreeNodeHeight(p) == binTreeNodeHeight(p->lc) + 1)
            && (isRed(p) && binTreeNodeHeight(p) == binTreeNodeHeight(p->lc));
    }
private:
    void solveDoubleRed(node_pointer);
    void solveDoubleBlack(node_pointer);
};

#endif //DATASTRUCT_REDBLACK_H