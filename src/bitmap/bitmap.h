//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_BITMAP_H
#define PLUS_BITMAP_H

#include <memory.h>
#include <cstddef>
#include <cassert>
#include <fstream>
#include <stdexcept>

/**
 * 位图Bitmap类
 *     位图是一种非常常见的结构，它使用每个二进制位来存放一个值的状态，正因为这个性质，它经常被用在数据压缩或者是索引等方面。
 */
class BitMap {
public:
    BitMap(size_t x = 20) { init(x); }
    ~BitMap() { delete _bits; }
    void set(size_t r);
    void reset(size_t r);
    bool test(size_t r);
    // [l, h)位转化为字符串
    char* toString(int lo, int hi);
    // 将位图整体导出至指定的文件，以便对此后的新位图批量初始化
    void dump(char* file);
    bool valid(int r);
private:
    size_t s;
    char* _bits;
    //若被访问的r已出界，则需扩容 (加倍策略)
    void expand(int r);
    void init(int r) { s = (r+7) >> 3; _bits = new char[s]; }
};

#endif //PLUS_BITMAP_H