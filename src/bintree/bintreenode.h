//
// Created by 张锐 on 2020/11/26.
//

#ifndef DATASTRUCT_BINTREENODE_H
#define DATASTRUCT_BINTREENODE_H

#define binTreeNodeHeight(x)  ( (x) ? (x)->height : -1 )

#include <cstddef>

/*
 树节点的性质：
    节点高度
    父/子节点指针
    数据
    状态：未知，发现，已访问
    颜色：红，黑
 */
template<typename T>
class bintreenode {
public:
    // 类型
    typedef bintreenode<T>* pointer;
    typedef const bintreenode<T>* const_pointer;
    typedef unsigned int Height;
    enum Color { red, black };
    enum Status { unknow, discover,visited };

    bintreenode():parent(nullptr),lc(nullptr),rc(nullptr),height(0),npl(1),color(black),status(unknow) {}
    bintreenode(const T&e, pointer p = nullptr, pointer l = nullptr, pointer r = nullptr, Height h = 0,
            int n = 1, Color c = black, Status s = unknow): data(e),parent(p),lc(l),rc(r),height(h),npl(n),color(c),status(s) {}

    // 基础方法支持
    pointer rightBrother() const {
        return isLc() ? parent->rc : nullptr;
    }
    bool hasParent() const { return parent; }
    bool hasLc() const { return lc; }
    bool hasRc() const { return rc; }
    bool hasChild() const { return lc || rc; }
    bool isLc() const { return hasParent() && parent->lc == this; }
    bool isRc() const { return hasParent() && parent->rc == this; }

    // 返回较高子节点，若子节点等高，返回与父节点同侧者
    pointer higherChildNode() {
        int hl = binTreeNodeHeight(lc);
        int hr = binTreeNodeHeight(rc);
        return hl > hr ? lc : ( hl < hr ? rc : ( isLc() ? lc : rc ) );
        return binTreeNodeHeight(lc) > binTreeNodeHeight(rc) ? lc : (
                binTreeNodeHeight(lc) < binTreeNodeHeight(rc) ? rc : ( isLc() ? lc : rc )
        );
    }

    size_t childs();    // 当前节点的子节点数目

    bool operator==(const_pointer rhs) const { return data == rhs->data; };
    bool operator<(const_pointer rhs) const { return data == rhs->data; };

    pointer insertAsLc(const T&);   // 不存在 lc 时的插入
    pointer insertAsRc(const T&);   // 不存在 rc 时的插入
    pointer succ() ;          // 中序遍历下的后继节点

    template <typename VST> void travelLevel ( VST& );    //子树层次遍历
    template <typename VST> void travelPre ( VST& );      //子树先序遍历
    template <typename VST> void travelIn ( VST& );       //子树中序遍历
    template <typename VST> void travelPost ( VST& );     //子树后序遍历

    pointer zig(); //对当前节点执行顺时针旋转
    pointer zag(); //对当前节点执行逆时针旋转

    // 未封装
    T data;
    pointer parent, lc, rc;
    Height height;
    int npl;    //Null Path Length（左式堆，也可直接用height代替）
    Color color;
    Status status;

private:
    template <typename VST> void travelPre1 ( VST& );      //子树先序遍历:递归
    template <typename VST> void travelPre2 ( VST& );      //子树先序遍历:迭代1
    template <typename VST> void travelPre3 ( VST& );      //子树先序遍历:迭代2
    template <typename VST> void travelPre4 ( VST& );      //子树先序遍历:迭代3
    template <typename VST> void travelIn1 ( VST& );       //子树中序遍历:递归
    template <typename VST> void travelIn2 ( VST& );       //子树中序遍历:迭代1
    template <typename VST> void travelIn3 ( VST& );       //子树中序遍历:迭代2
    template <typename VST> void travelIn4 ( VST& );       //子树中序遍历:迭代3
    template <typename VST> void travelPost1 ( VST& );     //子树后序遍历:递归
    template <typename VST> void travelPost2 ( VST& );     //子树后序遍历:迭代1
    template <typename VST> void travelPost3 ( VST& );      //子树后序遍历:迭代2
};

#endif //DATASTRUCT_BINTREENODE_H