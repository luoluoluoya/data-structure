//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_HUFFCHAR_H
#define PLUS_HUFFCHAR_H

struct HuffChar {
    char ch;
    int weight;
    HuffChar(char c = '^', int w = 0):ch(c), weight(w) {}
    bool operator<(const HuffChar &hc) { return weight < hc.weight; }
    bool operator==(const HuffChar &hc) {return weight == hc.weight; }
};

#endif //PLUS_HUFFCHAR_H

