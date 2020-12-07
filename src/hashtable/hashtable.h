//
// Created by 张锐 on 2020/12/7.
//

#ifndef DATASTRUCT_HASHTABLE_H
#define DATASTRUCT_HASHTABLE_H

#include "../entry/entry.h"
#include "../dictionary/dictionary.h"
#include "../bitmap/bitmap.h"
#include "../vector/vector.h"
#include <cstddef>

template<typename K, typename V>
class HashTable: public dictionary<K, V>{
public:
    typedef entry<K, V> elem_type;
    typedef entry<K, V>** entry_pointer;

    HashTable(int c = 193):_size(0), _buckets(vector<node*>(nextPrime(c), nextPrime(c), nullptr)) {}
    ~HashTable() { clear(); }

    int size() const { return _size; }
    int capacity() const { return _buckets.capacity(); }
    bool put(K, V);
    V* get(K);
    bool remove(K);
protected:
    //重散列算法：扩充桶数组，保证装填因子在警戒线以下
    void rehash();
    void clear();
    size_t hash(K);
private:
    // 存储的节点结构
    struct node {
        elem_type data;
        node* next;
        node(elem_type e, node* n = nullptr):data(e), next(n) {}
    };

    vector<node*> _buckets;
    int _size;

    unsigned long nextPrime(unsigned long n);
    void move(vector<node*>);
};

#endif //DATASTRUCT_HASHTABLE_H
