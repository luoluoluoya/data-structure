//
// Created by 张锐 on 2020/11/25.
//

#include "list.h"
#include <cassert>

template<typename T>
list<T>::list(const list<T> &rhs) {
    init();
    for (pointer p = rhs.front(), q = _header; p && p != rhs._trailer; p = p->succ)
        q = q->insertAsAfter(p->data);
}

template<typename T>
void list<T>::init() {
    _header = new listnode<T>(); _trailer = new listnode<T>();
    _header->succ = _trailer; _header->pred = nullptr;
    _trailer->pred = _header; _trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
void list<T>::clear() {
    pointer p = _trailer;
    while ( (p = p->pred) != _header ) delete p;
}

template<typename T>
list<T>::list(const_pointer p, size_type n) {
    init();
    pointer t = _header;
    for (size_type i = 0; i < n; i++, p = p->succ)
        t = t->insertAsAfter(p->data);
}
template<typename T>
list<T> & list<T>::operator=(const list<T>&rhs) {
    if ( &rhs == this ) return *this;
    clear();
    for (pointer p = rhs.front, t = _header; p && p != rhs._trailer; p = p->succ)
        t = t->insertAsAfter(p->data);
    return *this;
}
template<typename T>
typename list<T>::pointer list<T>::operator[](size_type n) {
    assert( 0 <= n && n < _size );
    pointer p = front();
    for (size_type i = 0; i < n; i++)
        p = p->succ;
    return p;
}
template<typename T>
typename list<T>::pointer list<T>::insertA(pointer p, const T &e) { ++_size; return p->insertAsAfter(e); }

template<typename T>
typename list<T>::pointer list<T>::insertB(pointer p, const T &e) { ++_size; return p->insertAsBefore(e); }

template<typename T>
typename list<T>::pointer list<T>::insertFront(const T &e) { ++_size; return _header->insertAsAfter(e); }

template<typename T>
typename list<T>::pointer list<T>::insertBack(const T &e) { ++_size; return _trailer->insertAsBefore(e); }

template<typename T>
T list<T>::remove(pointer p) {
    T e = p->data; //备份待删除节点的数值（假定T类型可直接赋值）
    p->pred->succ = p->succ; p->succ->pred = p->pred; //后继、前驱
    delete p; _size--; //释放节点，更新规模
    return e; //返回备份的数值
}
template<typename T>
bool list<T>::disordered() const {
    if (_size < 2) return true;
    bool sorted = true;
    for (pointer p = front()->succ; p != _trailer && (sorted = p->pred->data <= p->data); p = p->succ);
    return sorted;
}

template<typename T>
typename list<T>::pointer list<T>::find(const T&e, size_type n, pointer p) const {
    assert( 0 <= n && n <= _size );
    while ( 0 < n-- )
        if ( e == ( p = p->pred )->data ) return p; //逐个比对，直至命中或范围越界
    return nullptr; //p越出左边界意味着区间内不含e，查找失败
}

template<typename T>
typename list<T>::size_type list<T>::duplicate() {
    if (_size < 2) return 0;
    size_type oldSize = _size, r = 1;
    pointer p = front();
    while ( (p = p->succ) != _trailer ) {
        pointer ex = find(p->data, r, p);
        ex ? remove(ex) : r++;
    }
    return oldSize - _size;
}

template<typename T>
typename list<T>::size_type list<T>::uniquify() {
    if (_size < 2) return 0;
    size_type oldSize = _size;
    pointer p = front(), q; // p 前驱， q 后继
    while ( (q = p->succ) != _trailer ) {
        if (p->data != q->data)
            p = q;
        remove(p);
    }
    return oldSize - _size;
}
template<typename T>
void list<T>::reverse() {
    pointer p = _header, q = _trailer;      //头、尾节点
    for ( int i = 1; i < _size; i += 2 )    //（从首、末节点开始）由外而内，捉对地
        std::swap( ( p = p->succ )->data, ( q = q->pred )->data );  //交换对称节点的数据项
}

template<typename T>
typename list<T>::pointer list<T>::search(const T& e, size_type n, pointer p) const {
    while (n--)
        if ( (p = p->pred)->data <= e) break;
    return p;
}

template<typename T>
void list<T>::sort() {
    sort(_header->succ, _size);
}

template<typename T>
void list<T>::sort(pointer p, size_type n) {
    int num = rand() % 3;
    switch (num) {
        case 0:
            selectionSort(p, n);
            break;
        case 1:
            insertionSort(p, n);
            break;
        case 2:
            mergeSort(p, n);
            break;
    }
}

template<typename T>
void list<T>::merge(pointer &p, int n, list<T> &l, pointer q, int m) {
    pointer pp = p->pred; //借助前驱（可能是header），以便返回前 ...
    while ( 0 < m )       //在q尚未移出区间之前
        if ( ( 0 < n ) && ( p->data <= q->data ) )  //若p仍在区间内且v(p) <= v(q)，则
        { if ( q == ( p = p->succ ) ) break; n--; } //p归入合并的列表，并替换为其直接后继
        else //若p已超出右界或v(q) < v(p)，则
        { insertB ( p, l.remove ( ( q = q->succ )->pred ) ); m--; } //将q转移至p之前
    p = pp->succ; //确定归并后区间的（新）起点
}

template<typename T>
void list<T>::mergeSort(pointer &p, size_type n) {
    if ( n < 2 ) return; //若待排序范围已足够小，则直接返回；否则...
    int m = n >> 1; //以中点为界
    pointer q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //均分列表
    mergeSort ( p, m ); mergeSort ( q, n - m ); //对前、后子列表分别排序
    merge ( p, m, *this, q, n - m ); //归并
}


// todo
template<typename T>
void list<T>::selectionSort(pointer p, size_type n) {
    pointer head = p->pred; pointer tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->succ; //待排序区间为(head, tail)
    while ( 1 < n ) { //在至少还剩两个节点之前，在待排序区间内
        pointer max = selectMax ( head->succ, n ); //找出最大者（歧义时后者优先）
        insertB ( tail, remove ( max ) ); //将其移至无序区间末尾（作为有序区间新的首元素）
        tail = tail->pred; n--;
    }
}

template<typename T>
void list<T>::insertionSort(pointer p, size_type n) {
    for ( int r = 0; r < n; r++ ) { //逐一为各节点
        insertA ( search ( p->data, r, p ), p->data ); //查找适当的位置并插入
        p = p->succ; remove ( p->pred ); //转向下一节点
    }
}

//从起始于位置p的n个元素中选出最大者
template <typename T>
typename list<T>::pointer list<T>::selectMax( pointer p, size_type n ) {
    pointer max = p; //最大者暂定为首节点p
    for ( pointer cur = p; 1 < n; n-- ) //从首节点p出发，将后续节点逐一与max比较
        if ( !( ( cur = cur->succ )->data < max->data ) ) //若当前元素不小于max，则
            max = cur; //更新最大元素位置记录
    return max; //返回最大节点位置
}