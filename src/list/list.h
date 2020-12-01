//
// Created by 张锐 on 2020/11/25.
//

#ifndef DATASTRUCT_LIST_H
#define DATASTRUCT_LIST_H

#include "listnode.h"

template<typename T>
class list {
public:
    typedef typename listnode<T>::pointer pointer;
    typedef typename listnode<T>::const_pointer const_pointer;
    typedef size_t size_type;

    list() { init(); };
    list(const list<T> &);
    list(const_pointer, size_type);
    list &operator=(const list<T>&);
    ~list() { _size = 0; delete _header; delete _trailer; clear(); }

    // 容量
    size_type size() const { return _size; };
    bool empty() const { return !_size; };

    // 元素访问
    pointer front() const { return empty() ? nullptr : _header->succ; }
    pointer back() const  { return empty() ? nullptr : _trailer->pred; }
    pointer operator[](size_type s);

    bool valid(pointer p) { return p && p != _header && p != _trailer; }

    // 修改器
    pointer insertB(pointer, const T&);
    pointer insertA(pointer, const T&);
    pointer insertFront(const T&);
    pointer insertBack(const T&);
    T remove(pointer);

    // 算法
    bool disordered() const; //判断列表是否已排序

    void sort();

    pointer find(const T&e) const { return find(e, _size, _trailer); }          // 无序查找
    pointer find(const T&, size_type, pointer) const;                           // 在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
    pointer search(const T&e) const { return search(e, _size, _trailer); }      // 有序查找
    pointer search(const T&, size_type, pointer) const ;                        // 在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者

    size_type duplicate();
    size_type uniquify();
    void reverse(); //倒置

    void traverse(void (*visitor)(pointer)) { pointer p = _header; while ((p = p->succ) != _trailer) visitor(p); };

    pointer max() const { return selectMax(_header->succ, _size); }

protected:
    void init();
    pointer selectMax(pointer, size_type);
    void merge(pointer &p, int n, list<T>& L, pointer q, int m);    //有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
    void sort(pointer p, size_type t);   // 列表区间排序
    void insertionSort(pointer p, size_type t);
    void selectionSort(pointer p, size_type t);
    void mergeSort(pointer &p, size_type t);
private:
    pointer _header;
    pointer _trailer;
    size_type _size;
    void clear();   // 清空所有列表内的节点
};

#endif //DATASTRUCT_LIST_H
