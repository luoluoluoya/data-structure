//
// Created by 张锐 on 2020/11/27.
//

#ifndef DATASTRUCT_GRAPHMATRIX_H
#define DATASTRUCT_GRAPHMATRIX_H

#include "./graph.h"
#include "./graphnode.h"
#include "./graphedge.h"
#include <vector>

template<typename Tv, typename Te>
class graphmatrix: public graph<Tv, Te> {
public:
    typedef typename graphnode<Tv>::Status VStatus;
    typedef typename graphedge<Te>::Type EType;

    graphmatrix()=default;

    ~graphmatrix() {
        for (int i = 0; i < n; ++i) {
            delete vertexes[i];
            for (int j = 0; j < n; ++j) {
                delete edges[i][i];
            }
        }
    }

    /**顶点*/
    int insert(Tv const& e) {
        typename graphnode<Tv>::pointer np = new graphnode<Tv>(e);
        vertexes.push_back(np);
        for (int i = 0; i < n; ++i) {
            edges[i].push_back(nullptr);
        }

        std::vector<typename graphedge<Te>::pointer> rows(++n, nullptr);
        edges.push_back(rows);
        return n;
    }

    Tv remove(int v) {
        Tv d = vertexes[v]->data;
        for (int i = 0; i < n; ++i) {
            if ( edges[v][i] ) {
                delete edges[v][i];  vertexes[i]->inDegree--;
            }
        }
        for (int j = 0; j < n; ++j) {
            if ( edges[j][v] ) {
                delete edges[j][v]; vertexes[j]->outDegree--;
            }
//            edges[j].remove(v)
        }
//        vertexes.remove(v);
//        vertexes.remove(v);
        return d;
    }

    Tv &vertex(int v) { return vertexes[v]->data; }
    int inDegree(int v) {  return vertexes[v]->inDegree;  }
    int outDegree(int v) {  return vertexes[v]->outDegree;  }
    int firstNbr(int v) {
        int i = n-1;
        for (; i >= 0 && !exists(v, i); --i);
        return i;
    }

    int nextNbr(int v, int u) {
        int i = u-1;
        for (; i >= 0 && !exists(v, i); --i);
        return i;
    }

    VStatus &status(int v) { return vertexes[v]->status;  }
    int &dTime(int v) { return vertexes[v]->dTime;  }
    int &fTime(int v)  { return vertexes[v]->fTime;  }
    int parent(int v)  { return vertexes[v]->parent;  }
    int &priority(int v)  { return vertexes[v]->priority;  }
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    bool exists(int v, int u) { return edges[v][u]; }

    void insert(Te const& d, int v, int u, int w) {
        e++;
        typename graphedge<Te>::pointer ne = new graphedge<Te>(d, w);
        vertexes[v]->outDegree++; vertexes[u]->inDegree++;
        edges[v][u] = ne;
    }

    Te remove(int v, int u) {
        e--;
        Te d = edges[v][u]->data;
        vertexes[v]->outDegree--; vertexes[u]->inDegree--;
        delete edges[v][u];
        return d;
    }

    EType &type(int v, int u) { return edges[v][u]->type; }
    Te &edge(int v, int u) { return edges[v][u]->data; }
    int &weight(int v, int u) { return edges[v][u]->weight; }
private:
    int n; //顶点总数
    int e; //边总数

    std::vector<typename graphnode<Tv>::pointer> vertexes;
    std::vector<std::vector<typename graphedge<Te>::pointer>> edges;
};

#endif //DATASTRUCT_GRAPHMATRIX_H