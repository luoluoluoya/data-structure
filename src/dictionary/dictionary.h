//
// Created by 张锐 on 2020/12/3.
//

#ifndef DATASTRUCT_DICTIONARY_H
#define DATASTRUCT_DICTIONARY_H

//词典Dictionary模板类
template <typename K, typename V>
struct dictionary {
    virtual int size() const = 0;      //当前词条总数
    virtual bool put(K, V) = 0;      //插入词条（禁止雷同词条时可能失败）
    virtual V& get(K) = 0;          //读取词条
    virtual bool remove(K) = 0;    //删除词条
    V& operator[](K key) { return get(key); }
};

#endif //DATASTRUCT_DICTIONARY_H
