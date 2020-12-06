//
// Created by 47302 on 2020/12/6.
//

#include "bitmap.h"

bool BitMap::test(size_t x) {
    int index = x >> 32;
    int temp = x % 32;
    return (_bits[index] & (1 << temp)) ? 1 : 0;
}
void BitMap::reset(size_t x) {
    int index = x >> 32;
    int temp = x % 32;
    _bits[index] &= ~(1 << temp);
}
void BitMap::set(size_t x) {
    int index = x >> 5; //确定哪个数据（区间）
    int temp = x % 32;  //确定哪个Bit位
    _bits[index] |= (1 << temp);
}

char * BitMap::toString(int n) {
    char* s = new char[n + 1]; s[n] = '\0';
    for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
    return s;
}
