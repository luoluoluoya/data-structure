//
// Created by 张锐 on 2020/11/26.
//

#ifndef DATASTRUCT_BINTREE_H
#define DATASTRUCT_BINTREE_H

#include <cstddef>
#include "bintreenode.h"

template<typename T>
class bintree {
public:
    typedef bintree<T>* pointer;
    typedef bintree<T>* const_pointer;
    typedef typename bintreenode<T>::pointer node_pointer;
    typedef typename bintreenode<T>::const_pointer node_const_pointer;
    typedef size_t size_type;

    bintree():_root(nullptr),_size(0) {}
    bintree(const T&e):_root(new bintreenode<T>(e)),_size(1) {}
    ~bintree() { if (_size) remove(_root); }

    bool &operator==(const_pointer rhs) const { return _root && rhs->_root && _root == &rhs->_root; }

    size_type size() const { return _size; }
    bool empty() const { return _size == 0; }
    node_pointer root() { return _root; }


    node_pointer insertAsRoot (T const& e); //插入根节点（原无）
    node_pointer insertAsLc (node_pointer x, T const& e);   //e作为x的左孩子（原无）插入
    node_pointer insertAsRc (node_pointer x, T const& e);   //e作为x的右孩子（原无）插入
    node_pointer attachAsLc (node_pointer x, pointer t);   //t作为x左子树接入
    node_pointer attachAsRc (node_pointer x, pointer t);   //t作为x右子树接
    unsigned int remove (node_pointer x);                   //删除以位置x处节点为根的子树，返回移除的节点个数
    pointer secede (node_pointer x);                        //将子树x从当前树中摘除，并将其转换为一棵独立子树


    //层次遍历
    template <typename VST>
    void travLevel (VST& visit) { if ( _root ) _root->travelLevel (visit); }
    //先序遍历
    template <typename VST>
    void travPre (VST& visit) { if ( _root ) _root->travelPre (visit); }
    //中序遍历
    template <typename VST>
    void travIn (VST& visit) { if (_root) _root->travelIn (visit); }
    //后序遍历
    template <typename VST>
    void travPost (VST& visit) { if (_root) _root->travelPost (visit); }
protected:
    void updateHeight(node_pointer);
    void updateHeightAbove(node_pointer p) { while (p) { updateHeight(p); p = p->parent; } }
private:
    node_pointer _root;
    size_type _size;
};

#endif //DATASTRUCT_BINTREE_H
