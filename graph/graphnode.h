//
// Created by 张锐 on 2020/11/27.
//

#ifndef DATASTRUCT_GRAPHNODE_H
#define DATASTRUCT_GRAPHNODE_H

#include<climits>

template<typename Tv>
struct graphnode {
public:
    enum Status {undiscovered, discovered, visited };
    typedef graphnode<Tv>* pointer;

    graphnode(const Tv&e):data(e),status(undiscovered),dTime(0),fTime(0),inDegree(0),outDegree(0),parent(-1),priority(INT_MAX) {}

    Tv data;
    Status status;
    int dTime;
    int fTime;
    int inDegree;
    int outDegree;
    int parent;
    int priority;
};

#endif //DATASTRUCT_GRAPHNODE_H
