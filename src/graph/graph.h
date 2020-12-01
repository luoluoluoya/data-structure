//
// Created by 张锐 on 2020/11/27.
//

#ifndef DATASTRUCT_GRAPH_H
#define DATASTRUCT_GRAPH_H

#include "../stack/stack.h"
#include <cstddef>
#include "graphnode.h"
#include "graphedge.h"

/**
 * 图的抽象结构：定义图结构所支持的各种算法；
 *  具体的实现形式由不同的存储形式决定
 *
 * @tparam Tv
 * @tparam Te
 */
template<typename Tv, typename Te>
class graph {
public:
    typedef typename graphnode<Tv>::Status VStatus;
    typedef typename graphedge<Te>::Type EType;

    int vSize() const { return n; }
    int eSize() const { return e; }

    /**顶点*/
    virtual int insert(Tv const&) = 0; //插入顶点，返回编号
    virtual Tv remove(int) = 0;        //删除顶点及其关联边，返回该顶点信息
    virtual Tv&vertex(int) = 0;        //顶点v的数据（该顶点的确存在）
    virtual int inDegree(int) = 0;     //顶点v的入度（该顶点的确存在）
    virtual int outDegree(int) = 0;    //顶点v的出度（该顶点的确存在）
    virtual int firstNbr(int) = 0;     //顶点v的首个邻接顶点
    virtual int nextNbr(int, int) = 0; //顶点v的（相对于顶点j的）下一邻接顶点
    virtual VStatus&status(int) = 0;   //顶点v的状态
    virtual int&dTime(int) = 0;        //顶点v的时间标签dTime
    virtual int&fTime(int) = 0;        //顶点v的时间标签fTime
    virtual int&parent(int) = 0;       //顶点v在遍历树中的父亲
    virtual int&priority(int) = 0;     //顶点v在遍历树中的优先级数
    /**边：无向边均统一转化为方向互逆的一对有向边**/
    virtual bool exists(int, int) = 0; //边(v, u)是否存在
    virtual void insert(int, int, Te const&, int) = 0; //在顶点v和u之间插入权重为w的边e
    virtual Te remove(int, int) = 0;   //删除顶点v和u之间的边e，返回该边信息
    virtual EType &type(int, int) = 0; //边(v, u)的类型
    virtual Te&edge(int, int) = 0;     //边(v, u)的数据（该边的确存在）
    virtual int&weight(int, int) = 0;  //边(v, u)的权重
    /**算法*/
    void bfs(int);                      //广度优先搜索算法
    void dfs(int);                      //深度优先搜索算法
    void bcc(int);                      //基于DFS的双连通分量分解算法
    stack<Tv> tSort(int);         //基于DFS的拓扑排序算法
    void prim(int);                     //最小支撑树Prim算法
    void dijkstra(int);                 //最短路径Dijkstra算法
    template <typename PU> void pfs(int, PU); //优先级搜索框架
    void bfsPU(int);          // 广度优先搜索: 优先级算法
    void dfsPU(int);          // 深度优先搜索: 优先级算法
    void primPU(int);         // 最小支撑树Prim算法: 优先级算法
    void dijkstraPU(int);     // 最短路径Dijkstra算法: 优先级算法

protected:
    int n; //顶点总数
    int e; //边总数

    void reset() {
        for (int i = 0; i < n; i++) {
            // 顶点
            status(i) = graphnode<Tv>::undiscovered;
            dTime(i) = fTime(i) = 0;
            parent(i) = -1;
            priority(i) = INT_MAX;
            // 边
            for (int j = 0; j < n; ++j) {
                if (exists(i, j)) type(i, j) = graphedge<Te>::undetermined;
            }
        }
    }
    void BFS(int, unsigned int&); //（连通域）广度优先搜索算法
    void DFS(int, unsigned int&); //（连通域）深度优先搜索算法
    void BCC(int, unsigned int&, stack<int>&);   //（连通域）基于DFS的双连通分量分解算法
    bool TSort(int, unsigned int&, stack<Tv>&);  //（连通域）基于DFS的拓扑排序算法
    template <typename PU> void PFS(int, PU); //（连通域）优先级搜索框架
};

#endif //DATASTRUCT_GRAPH_H
