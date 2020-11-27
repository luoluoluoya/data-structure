//
// Created by 张锐 on 2020/11/27.
//

#ifndef DATASTRUCT_GRAPHEDGE_H
#define DATASTRUCT_GRAPHEDGE_H

template<typename Te>
struct graphedge {
public:
    typedef graphedge<Te>* pointer;
    enum Type { undetermined, tree, froward, backword, cross };

    graphedge(const Te&d, int w = 0):data(d),type(undetermined),weight(w) {}

    Te data;
    int weight;
    Type type;
};

#endif //DATASTRUCT_GRAPHEDGE_H
