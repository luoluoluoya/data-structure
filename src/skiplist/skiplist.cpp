//
// Created by 张锐 on 2020/12/3.
//

#include "skiplist.h"
#include <cstdlib>

template <typename K, typename V>
bool skiplist<K, V>::put(K key, V val) {
    elem_type e = entry<K, V>(key, val);
    if (empty())
        _elem.insertFront(new quadlist<elem_type>());
    layer_node_pointer l = _elem.front();
    quadlistnode<elem_type>* p = l->data->first();
    if (skipSearch(l, p, key))
        while (p->blow) p = p->blow;
    l = _elem.back();
    auto b = l->data->insertAfterAbove(e, p, nullptr);
    while (rand() & 1) {
        while (l->data->valid(p) && !p->above) p = p->pred;
        if (!l->data->valid(p)) {
            if (l == _elem.front()) {
                _elem.insertFront(new quadlist<entry<K, V>>());
            }
            p = l->pred->data->first()->pred;
        } else {
            p = p->above;
        }
        l = l->pred;
        b = l->data->insertAfterAbove(e, p, b);
    }
    return true;
}

template <typename K, typename V>
V* skiplist<K, V>::get(K key) {
    if (empty())
        return nullptr;
    layer_node_pointer l = _elem.front();
    quadlistnode<elem_type>* p = l->data->first();
    return skipSearch(l, p, key) ? &(p->entry.value) : nullptr;
}

template <typename K, typename V>
bool skiplist<K, V>::remove(K key) {
    if (empty())
        return false;
    // 从顶层开始查找，未找到元素返回
    layer_node_pointer l = _elem.front();
    quadlistnode<elem_type>* p = l->data->first();
    if (!skipSearch(l, p, key))
        return false;

    // 执行删除
    do {
        auto lower = p->blow;
        l->data->remove(p);
        p = lower; l = l->succ;
    } while (l->succ);

    // 移除不含节点的层
    while (!empty() && _elem.front()->data->empty())
        _elem.remove(_elem.front());
    return true;
}

template<typename K, typename V>
bool skiplist<K, V>::skipSearch(layer_node_pointer &layer, quadlistnode<elem_type>* &p, K &key) {
    while (layer->succ) {
        // 当前层内查找
        while (p->succ && p->entry <= key) p = p->succ;
        p = p->pred;
        // 判断是否找到
        if (p->pred && p->entry == key)
            return true;
        // 深入下一层
        layer = layer->succ;
        if (!layer->succ)
            return false;
        p = p->pred ? p->blow : layer->data->first();
    }
}