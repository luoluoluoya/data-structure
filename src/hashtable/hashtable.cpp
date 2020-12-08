//
// Created by 张锐 on 2020/12/7.
//

#include "hashtable.h"

static size_t hashCode(char c) { return(size_t) c; }
static size_t hashCode(int k) { return(size_t) k; }
static size_t hashCode(long long i) {
    return(size_t)(( i >> 32) +(int) i);
}
static size_t hashCode(char s[]) {
    int h = 0;
    for(size_t n = strlen(s), i = 0; i < n; i++){
        h =(h << 5) |(h >> 27);
        h +=(int) s[i];
    }
    return(size_t) h;
}

template<typename K, typename V>
unsigned long HashTable<K, V>::HashTable::nextPrime(unsigned long n) {
    static const int num_primes = 28;
    static const unsigned long prime_list[num_primes] = { 53, 97, 193, 389, 769,
                                                          1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
                                                          786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653,
                                                          100663319, 201326611, 402653189, 805306457, 1610612741,
                                                          3221225473ul, 4294967291ul };
    //  寻找大于等于 n 且最接近 n 的质数
    int i = 0;
    while (i < num_primes && prime_list[i] < n)
        i++;
    return i == num_primes ? prime_list[num_primes - 1] : prime_list[i];
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    //  清除所有链中的节点
    for (int i = 0; i < _buckets.size(); ++i) {
        node* p = _buckets[i];
        while (p) {
            node* n = p->next;
            delete p;
            p = n;
        }
    }
}

template<typename K, typename V>
size_t HashTable<K, V>::hash(K key) {
    return hashCode(key) % _buckets.capacity();
}

template<typename K, typename V>
bool HashTable<K, V>::put(K key, V val) {
    size_t i = hash(key);
    node* &p = _buckets[i];
    while (p) {
        if (p->data == val) return false;
        p = p->next;
    }
    p = new node(entry<K, V>(key, val)); ++_size; _tags.set(i);
    return true;
}

template<typename K, typename V>
V& HashTable<K, V>::get(K key) {
    size_t i = hash(key);
    node* p = _buckets[i]; node* u = nullptr;
    while (p && p->data != key) {
        u = p; p = p->next;
    }
    if (!p) {
        p = new node(entry<K, V>(key, V())); ++_size; _tags.set(i);
        (u ? u->next : _buckets[i]) = p;
    }
    return p->data.value;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(K key) {
    size_t i = hash(key);
    node* p = _buckets[i]; node* u = nullptr;
    while (p && p->data != key) {
        u = p; p = p->next;
    }
    if (!p)
        return false;
    if (!u) {
        _buckets[i] = p->next; if (!_buckets[i]) _tags.reset(i);
    } else
        u->next = p->next;
    delete p; --_size;
    return true;
}

// todo 此处应当使用BitMap已提高效率
// 保证填充因子处于一个合理的范围一提高效率
// 1/4 ~ 3/4
template<typename K, typename V>
void HashTable<K, V>::rehash() {
    if ( capacity()/4 <= size() && size()*4 <= capacity()*3 )
        return;
    int ns = capacity() >> 2 > size() ? capacity() >> 1 : capacity() << 1; vector<node *> nv(ns, ns, nullptr);

}
