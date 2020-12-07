//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_BITMAP_H
#define PLUS_BITMAP_H

#include <memory.h>
#include "../vector/vector.h"

/**
 * 位图Bitmap类
 *     位图是一种非常常见的结构，它使用每个二进制位来存放一个值的状态，正因为这个性质，它经常被用在数据压缩或者是索引等方面。
 *     有这样一道题：给40亿个不重复的无符号整数，没有经过排序，然后再给一个树，如何快速判断这个数是否在40亿个数之中？在这里如果我们实打实
 *     的存放40亿个数据在内存中，那会占据将近15个G的内存，普通电脑根本无法满足，更不用说在对其进行查找操作了。 那么如果选择位图来存储的话
 *     我们只需要差不多500M就够了。大大的节省了内存的消耗。
 */
class BitMap {
public:
    BitMap(size_t range = 20):_bits(range >> 5) {}

    void set(size_t x);

    void reset(size_t x);

    bool test(size_t x);

    char *toString(int n); // 前n位转化为字符串
private:
    vector<int> _bits;
};


#endif //PLUS_BITMAP_H
