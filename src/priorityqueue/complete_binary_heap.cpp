//
// Created by 47302 on 2020/12/6.
//

#include "complete_binary_heap.h"

template<typename T>
T CompleteBinaryHeap<T>::delMax() {
    assert(size() > 0);
    std::swap(_elem[0], _elem[_elem.size()-1]);
    T e = _elem.remove(_elem.size()-1);
    downRepair(0);
    return e;
}

template<typename T>
void CompleteBinaryHeap<T>::upRepair(int r) {
    int p;
    while (valid(p = parent(r))) {
        if (_elem[p] >= _elem[r]) break;
        std::swap(_elem[p], _elem[r]); r = p;
    }
}

template<typename T>
void CompleteBinaryHeap<T>::downRepair(int r) {
    while (valid(r)) {
        int larger = largerLcAndRc(r);
        if (larger == r) break;
        std::swap(_elem[r], _elem[larger]); r = larger;
    }
}

template<typename T>
CompleteBinaryHeap<T>::CompleteBinaryHeap(T *elements, int size):_elem(vector<T>()){
    for (int i = 0; i < size; ++i)
        _elem.insert(elements[i]);
    heapify();
}

template<typename T>
void CompleteBinaryHeap<T>::heapify() {
    int in = parent(_elem.size()-1);
    while (valid(in)) {
        //printf("doing downRepair %d\n", in);
        downRepair(in); --in;
    }
}