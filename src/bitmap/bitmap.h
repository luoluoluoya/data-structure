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

//class BitMap { //位图Bitmap类
//private:
//    char *M;
//    int N; //比特图所存放的空间M[]，容量为N*sizeof(char)*8比特
//protected:
//    void init(int n) {
//        M = new char[N = (n + 7) / 8];
//        memset(M, 0, N);
//    }
//
//public:
//    Bitmap(int n = 8) { init(n); } //按指定或默认规模创建比特图（为测试暂时选用较小的默认值）
//    Bitmap(char *file, int n = 8) //按指定或默认规模，从指定文件中读取比特图
//    {
//        init(n);
//        FILE *fp = fopen(file, "r");
//        fread(M, sizeof(char), N, fp);
//        fclose(fp);
//    }
//
//    ~Bitmap() {
//        delete[] M;
//        M = NULL;
//    } //析构时释放比特图空间
//
//    void set(int k) {
//        expand(k);
//        M[k >> 3] |= (0x80 >> (k & 0x07));
//    }
//
//    void clear(int k) {
//        expand(k);
//        M[k >> 3] &= ~(0x80 >> (k & 0x07));
//    }
//
//    bool test(int k) {
//        expand(k);
//        return M[k >> 3] & (0x80 >> (k & 0x07));
//    }
//
//    void dump(char *file) //将位图整体导出至指定的文件，以便对此后的新位图批量初始化
//    {
//        FILE *fp = fopen(file, "w");
//        fwrite(M, sizeof(char), N, fp);
//        fclose(fp);
//    }
//
//    char *bits2string(int n) { //将前n位转换为字符串——
//        expand(n - 1); //此时可能被访问的最高位为bitmap[n - 1]
//        char *s = new char[n + 1];
//        s[n] = '\0'; //字符串所占空间，由上层调用者负责释放
//        for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
//        return s; //返回字符串位置
//    }
//
//    //若被访问的Bitmap[k]已出界，则需扩容.
//    void expand(int k) {
//        if (k < 8 * N) return;
//        int oldN = N;
//        char *oldM = M;
//        init(2 * k);
//        memcpy_s(M, N, oldM, oldN);
//        delete[] oldM;
//    }
//};

#endif //PLUS_BITMAP_H
