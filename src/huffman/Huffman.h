//
// Created by 47302 on 2020/12/7.
//

#ifndef PLUS_HUFFMAN_H
#define PLUS_HUFFMAN_H

#include "../bitmap/bitmap.h"
#include "../bintree/bintree.h"
#include "huffchar.h"
#include "../priorityqueue/complete_binary_heap.h"
#include "../hashtable/hashtable.h"
#include <string>
#include <map>

typedef bintree<HuffChar> HuffTree;
typedef CompleteBinaryHeap<HuffTree *> HuffForest;  // 基于完全二叉堆所构造的森林
typedef std::map<char, int> Frequency;
typedef std::map<char, std::string> CodeTable;

//分析输入文件，统计各字符的出现频率
Frequency statistics(std::string fName);

//依据统计各字符的出现频率构造森林
HuffForest* constructHuffForest(Frequency);

// 根据编码树森林生成最优编码树
HuffTree* constructHuffTree(HuffForest*);

// 依据编码树生成编码表
CodeTable constructCodeTable(HuffTree*);

// 编码文件
void encode(std::string source);

// 解码文件
void decode(HuffTree tree, std::string source);

#endif //PLUS_HUFFMAN_H
