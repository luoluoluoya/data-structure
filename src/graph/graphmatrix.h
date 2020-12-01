//
// Created by 张锐 on 2020/11/27.
//

#ifndef DATASTRUCT_GRAPHMATRIX_H
#define DATASTRUCT_GRAPHMATRIX_H

#include "./graph.h"
#include "./graphnode.h"
#include "./graphedge.h"
#include <vector>
#include "../vector/vector.h"

template<typename Tv, typename Te>
class graphmatrix: public graph<Tv, Te>{
public:
    typedef typename graphnode<Tv>::Status VStatus;
    typedef typename graphedge<Te>::Type EType;
    typedef typename graphnode<Tv>::pointer node_pointer;
    typedef typename graphedge<Te>::pointer edge_pointer;

    graphmatrix()=default;

    /**顶点*/
    int insert(Tv const& e) {
        node_pointer vPointer = new graphnode<Tv>(e);
        for (int i = 0; i < this->n; ++i)
            edges[i].insert(nullptr);
        ++this->n;
        edges.insert(vector<edge_pointer>(this->n, this->n, nullptr));
        return vertexes.insert(vPointer);
    }

    Tv remove(int v) {
        //所有出边逐条删除
        for (int j = 0; j < this->n; j++)
            if (exists (v, j)) { delete edges[v][j];  vertexes[j]->inDegree--; }

        //删除第i行
        edges.remove(v); this->n--;
        //删除顶点i
        Tv vBak = vertex (v); vertexes.remove (v);

        //所有入边逐条删除
        for (int j = 0; j < this->n; j++)
            if (edge_pointer e = edges[j].remove(v)) { delete e; vertexes[j]->outDegree--; }
        return vBak;
    }

    Tv &vertex(int v) { return vertexes[v]->data; }
    int inDegree(int v) {  return vertexes[v]->inDegree;  }
    int outDegree(int v) {  return vertexes[v]->outDegree;  }

    // 相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
    int firstNbr(int v) { return nextNbr(v, this->n); }
    int nextNbr(int i, int j) {
        while ( (-1 < j) && (!exists(i, --j)) ); return j;
    }

    VStatus &status(int v) { return vertexes[v]->status;  }
    int &dTime(int v) { return vertexes[v]->dTime;  }
    int &fTime(int v)  { return vertexes[v]->fTime;  }
    int &parent(int v)  { return vertexes[v]->parent;  }
    int &priority(int v)  { return vertexes[v]->priority;  }
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    bool exists(int v, int u) {  return ( 0 <= v ) && ( v < this->n ) && ( 0 <= u ) && ( u < this->n ) && edges[v][u] != NULL; }

    void insert(int v, int u, Te const&d, int w) {
        assert(!exists(v, u));
        this->e++;
        typename graphedge<Te>::pointer ne = new graphedge<Te>(d, w);
        vertexes[v]->outDegree++; vertexes[u]->inDegree++;
        edges[v][u] = ne;
    }

    Te remove(int v, int u) {
        assert(exists(v, u));
        this->e--;
        Te d = edges[v][u]->data;
        vertexes[v]->outDegree--; vertexes[u]->inDegree--;
        delete edges[v][u];
        return d;
    }

    EType &type(int v, int u) { assert(exists(v, u)); return edges[v][u]->type; }
    Te &edge(int v, int u) { assert(exists(v, u)); return edges[v][u]->data; }
    int &weight(int v, int u) { assert(exists(v, u)); return edges[v][u]->weight; }
private:
    // 定点和边
    vector<node_pointer> vertexes;
    vector<vector<edge_pointer>> edges;
};

#endif //DATASTRUCT_GRAPHMATRIX_H