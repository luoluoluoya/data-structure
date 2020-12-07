//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_ENTRY_H
#define DATASTRUCT_ENTRY_H

template <typename K, typename V>
struct entry {
    K key; V value; //关键码、数值

    //默认构造函数
    entry (K k = K(), V v = V()) : key (k), value (v) {};
    //基于克隆的构造函数
    entry (entry<K, V> const& e) : key (e.key), value (e.value) {};

    bool operator< (entry<K, V> const& e) { return key <  e.key; }  //比较器：小于
    bool operator<= (entry<K, V> const& e) { return key <=  e.key; }  //比较器：小于
    bool operator> (entry<K, V> const& e) { return key >  e.key; }  //比较器：大于
    bool operator>= (entry<K, V> const& e) { return key >=  e.key; }  //比较器：大于
    bool operator== (entry<K, V> const& e) { return key == e.key; } //判等器：等于
    bool operator!= (entry<K, V> const& e) { return key != e.key; } //判等器：不等于

    bool operator< (K k) { return key <  k; }  //比较器：小于
    bool operator<= (K k) { return key <=  k; }  //比较器：小于
    bool operator> (K k) { return key >  k; }  //比较器：大于
    bool operator>= (K k) { return key >=  k; }  //比较器：大于
    bool operator== (K k) { return key == k; } //判等器：等于
    bool operator!= (K k) { return key != k; } //判等器：不等于
};

#endif //DATASTRUCT_ENTRY_H
