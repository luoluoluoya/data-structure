//
// Created by 47302 on 2020/12/6.
//

#include "bitmap.h"

bool BitMap::test(size_t r) { expand(r); return _bits[r>>3] & (0x80 >> (r & 0x07)); }
void BitMap::reset(size_t r) { expand(r); _bits[r>>3] &= ~(0x80 >> (r & 0x07)); }
void BitMap::set(size_t r) { expand(r); _bits[r>>3] |= (0x80 >> (r & 0x07)); }

bool BitMap::valid(int r) { return 0 <= r && r < s; }

char* BitMap::toString(int lo, int hi) {
    assert(0 <= lo && lo <=hi);
    expand(hi-1);
    char *str = new char[hi-lo];
    for (int i = lo, j = 0; i < hi; ++i, ++j) {
        str[j] = test(i) ? '1' : '0';
    }
    return str;
}

void BitMap::dump(char *file) {
    std::ofstream out(file, std::ios ::binary);
    if (!out.is_open())
        throw std::runtime_error("文件打开失败!");
    out.write(_bits, sizeof(_bits));
    out.close();
}

void BitMap::expand(int r) {
    if (r < 8*s) return;
    int oldS = s; char* oldB = _bits;
    init(r*2);
    memcpy(oldB, _bits, oldS); delete oldB;
}
