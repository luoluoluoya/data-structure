//
// Created by 47302 on 2020/12/7.
//

#include "huffman.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

static void travel(bintreenode<HuffChar>* x, BitMap& code, int length, CodeTable& table) {
    if(!x->hasChild()) {
        table[x->data.ch] = code.toString(length); return ;
    }
    if(x->hasLc()) {
        code.reset(length); travel(x->lc, code, length+1, table);
    }
    if(x->hasRc()) {
        code.set(length); travel(x->rc, code, length+1, table);
    }
}

Frequency statistics(std::string fName)
{
    Frequency frequency;
    std::fstream in(fName);
    if (!in.is_open())
        throw std::runtime_error("文件打开失败!");
    while (in.eof()) ++frequency[in.get()];
    in.close();
    return frequency;
}

HuffForest* constructHuffForest(Frequency frequency) {
    HuffForest* forest = new HuffForest;
    auto iter = frequency.begin();
    while(iter != frequency.end()) {
        forest->insert( new HuffTree(HuffChar(iter->first, iter->second)) );
        iter++;
    }
    return forest;
}

HuffTree* constructHuffTree(HuffForest* forest) {
    while(forest->size() > 1) {
        HuffTree* t1 = forest->getMax();
        HuffTree* t2 = forest->getMax();
        forest->insert( new HuffTree(HuffChar('^', t1->root()->data.weight + t2->root()->data.weight)) );
    }
    return forest->delMax();
}

CodeTable constructCodeTable(HuffTree* tree) {
    CodeTable table;
    BitMap code;
    travel(tree->root(), code, 0, table);
    return table;
}

void encode(std::string source)
{
    Frequency frequency = statistics(source);
    HuffForest* forest = constructHuffForest(frequency);
    HuffTree* tree = constructHuffTree(forest);
    CodeTable table = constructCodeTable(tree);
    std::fstream in(source);
    while (in.eof())
        std::cout << table[in.get()];
    in.close();
}

void decode(HuffTree tree, std::string source) {
    std::fstream in(source, std::fstream::binary);
    if (!in.is_open())
        throw std::runtime_error("文件打开失败!");
    while (in.eof()) { // todo
    }
}