//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_SKIPLIST_H
#define DATASTRUCT_SKIPLIST_H

#include "quadlist.h"
#include "../list/list.h"
#include "../dictionary/dictionary.h"
#include "../entry/entry.h"

template<typename K, typename V>
class skiplist: public dictionary<K, V>{
public:
    typedef entry<K, V> elem_type;                               // 存储的元素类型
    typedef listnode<quadlist<elem_type>*>* layer_node_pointer;  // 节点指针（层）

    skiplist():_elem(list<quadlist<elem_type>*>()) {}

    bool empty() const { return size() < 1; }
    int level() const { return _elem.size(); }
    int size() const { return _elem.empty() ? 0 : _elem.back()->data->size(); }
    bool put(K, V);
    V* get(K);
    bool remove(K);
protected:
    // 从第layer层的p节点开始寻找k
    bool skipSearch(layer_node_pointer &layer, quadlistnode<elem_type>* &p, K &k);
private:
    list<quadlist<elem_type>*> _elem;
};

#endif //DATASTRUCT_SKIPLIST_H
