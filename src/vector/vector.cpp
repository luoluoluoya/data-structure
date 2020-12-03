//
// Created by 张锐 on 2020/11/24.
//

#include "vector.h"
#include <cassert>
#include <random>
#include <algorithm>

template<typename T>
inline vector<T>::vector(rank c):_capacity(c),_size(0),_elements(new T[_capacity]){}

template<typename T>
vector<T>::vector(rank c, rank s, const T&e):_capacity(c),_size(s),_elements(new T[_capacity]){
    while (s--)
        _elements[s] = e;
}

template<typename T>
vector<T>::vector(const vector<T> &rhs):_capacity(rhs._capacity),_size(rhs._size), _elements(new T[_capacity]){
    copy(_elements, rhs._elements, _size);
}

template<typename T>
vector<T> & vector<T>::operator=(const vector<T> &rhs) {
    auto other = new T[rhs._capacity];
    copy(other, rhs._elements, rhs._size);
    clear();
    _size = rhs._size;
    _capacity = rhs._capacity;
    _elements = other;
    return *this;
}

template<typename T>
vector<T>::~vector<T>() {
    clear();
}

template<typename T>
typename vector<T>::reference vector<T>::operator[](rank i) {
    assert(i >= 0 && i < _size);
    return _elements[i];
}

template<typename T>
typename vector<T>::reference vector<T>::at(rank i) {
    assert(i >= 0 && i < _size);
    return _elements[i];
}

template<typename T>
typename vector<T>::rank vector<T>::insert(rank r, const T &e) {
    assert(r >= 0 && r <= _size);
    expand();   // 扩容
    for (int i = _size; i > r; --i)
        _elements[_size] = _elements[_size - 1];
    _elements[r] = e;
    _size++;
    return r;
}

template<typename T>
typename vector<T>::rank vector<T>::insert(const T& e) {
    return insert(_size, e);
}

template<typename T>
T vector<T>::remove(rank r) {
    T e = *(_elements+r);
    remove(r, r+1);
    return e;
}

template<typename T>
int vector<T>::remove(rank lo, rank hi) {
    assert(0 <= lo && lo <= hi && hi <= _size);
    rank s = _size;
    while (hi < _size)
        _elements[lo++] = _elements[hi++];
    _size = lo;
    shrink();
    return _size - s;
}

template<typename T>
void vector<T>::clear() {
    delete [] _elements;
}

template<typename T>
bool vector<T>::disordered() const {
    int i = 1;
    bool sorted = true;
    while (i < _size && !(sorted = _elements[i-1] <= _elements[i]));
    return sorted;
}

template<typename T>
void vector<T>::unsort() {
    unsort(0, _size);
}

template<typename T>
void vector<T>::unsort(rank lo, rank hi) {
    assert(0 <= lo && lo <= hi && hi <= _size);
    pointer st = _elements + lo;
    for (rank i = hi - lo; i > 0; --i)
        std::swap(st[ i-1 ], st[ rand() % i ]);
}

template<typename T>
int vector<T>::deduplicate() {
    int r = 1, s = _size;
    while (r < _size)
        find(_elements[r], 0, r) == -1 ? r++ : remove(r);
    shrink();
    return s - _size;
}

template<typename T>
int vector<T>::uniquify() {
    int p = 0, q = p, s = _size;
    while (q++ < _size)
        if (_elements[p] != _elements[q])
            _elements[++p] = _elements[q];
    _size = p;
    return s - _size;
}

template<typename T>
int vector<T>::find(const T &e) const {
    return find(e, 0, _size);
}

template<typename T>
int vector<T>::find(const T &e, rank lo, rank hi) const {
    assert(0 <= lo && lo <= hi && hi <= _size);
    while (lo < hi--)
        if (_elements[hi] == e)
            break;
    return hi;
}

template<typename T>
int vector<T>::search(const T &e) const {
    return search(e, 0, _size);
}

// 返回不大于 e 的关键码
template<typename T>
int vector<T>::search(const T&e, rank lo, rank hi) const {
    while (lo < hi) {
        rank mid = (lo + hi) >> 1;
        e < _elements[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}

template<typename T>
bool vector<T>::bubble(rank lo, rank hi) {
    bool sorted = true;
    while (++lo < hi)
        if (_elements[lo-1] > _elements[lo]) {
            sorted = false;
            std::swap(_elements[ lo-1 ], _elements[lo]);
        }
    return sorted;
}

template<typename T>
void vector<T>::bubbleSort(rank lo, rank hi) {
    while (lo < hi && !bubble(lo, hi)) hi--;
}

template<typename T>
typename vector<T>::rank vector<T>::max(rank lo, rank hi) {
    rank max = hi -1;
    while (lo < hi--)
        if (_elements[hi] > _elements[max])
            max = hi;
    return max;
}

template<typename T>
void vector<T>::selectionSort(rank lo, rank hi) {
    while (lo < hi)
        std::swap(_elements[ max(lo, hi) ], _elements[--hi]);
}

template<typename T>
void vector<T>::merge(rank lo, rank mi, rank hi) {
    rank lsize = mi - lo;
    pointer lef = new T[lsize];
    copy(lef, _elements + lo, lsize);
    for (rank i = 0, j = mi, k = lo; i < lsize || j < hi;) {    // 总共需要移动 hi - lo 个元素； 没步迭代，要么 i++/j++
        if (i >= lsize || (j < hi && lef[i] > _elements[j]))  //
            _elements[k++] = _elements[j++];
        else
            _elements[k++] = lef[i++];
    }
    delete []lef;
}

template<typename T>
void vector<T>::mergeSort(rank lo, rank hi) {
    if (hi - lo < 2) return;
    rank mid = (lo + hi) >> 1;
    mergeSort(lo, mid);  mergeSort(mid, hi);
    merge(lo, mid, hi);
}

template<typename T>
void vector<T>::traverse(void (*p)(reference)) const {
    for (int i = 0; i < _size; ++i)
        p(_elements[i]);
}

template<typename T>
void vector<T>::copy(pointer lhs, pointer rhs, rank n) {
    for (rank i = 0; i < n; i++)
        *(lhs+i) = *(rhs+i);
}

template<typename T>
void vector<T>::expand() {
    if (_size == _capacity) {
        _capacity > 0 ? (_capacity <<= 1) : (_capacity = 3);
        pointer cp = new T[_capacity];
        copy(cp, _elements, _size);
        delete [] _elements;
        _elements = cp;
    }
}

template<typename T>
void vector<T>::shrink() {
    if ((_size << 2) < _capacity) {
        pointer cp = new T[ _capacity >>= 1 ];
        copy(cp, _elements, _size);
        delete [] _elements;
        _elements = cp;
    }
}

template<typename T>
void vector<T>::sort() {
    sort(0, _size);
}


template<typename T>
void vector<T>::sort(rank lo, rank hi) {
    int num = rand() % 3;
    switch (num) {
        case 0:
            bubbleSort(lo, hi);
            break;
        case 1:
            mergeSort(lo, hi);
            break;
        case 2:
            selectionSort(lo, hi);
            break;
    }
}

//template<typename T>
//vector<T>::