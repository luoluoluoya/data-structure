//
// Created by 张锐 on 2020/12/1.
//


#include "./src/queue/queue.h"
#include "./src/vector/vector.h"
#include "./src/queue/queue.cpp"
#include "./src/stack/stack.cpp"
#include "./src/vector/vector.cpp"
#include "./src/list/list.h"
#include "./src/list/list.cpp"
#include "./src/list/listnode.h"
#include "./src/list/listnode.cpp"
#include <iostream>
#include "./src/bintree/bintreenode.cpp"
#include "./src/bintree/bintree.cpp"
#include "./src/bst/bst.h"
#include "./src/bst/bst.cpp"
#include "./src/avl/avl.h"
#include "./src/avl/avl.cpp"
#include "./src/graph/graphmatrix.h"
#include "./src/graph/graphedge.h"
//#include "./src/graph/graph.h"
#include "./src/graph/graph.cpp"

template<typename Tv, typename Te>
class GraphMatrixTravlier {
public:
    void operator()(graphmatrix<Tv, Te> &g){
        std::cout << "Print The Grapth: vsize " << g.vSize() << ", eSize " << g.eSize() << std::endl;
        for (int i = 0; i < g.vSize(); ++i) {
            for (int j = 0; j < g.vSize(); ++j) {
                std::cout << "Node " << g.vertex(i) << ":" << " indegree:" << g.inDegree(i) << " outDegree:" << g.outDegree(i) <<
                          "; Node " << g.vertex(j) << ":" << " indegree:" << g.inDegree(j) << " outDegree:" << g.outDegree(j) <<
                          "; Edge(" << g.vertex(i) << g.vertex(j) << "): " << ( g.exists(i, j) ? "Exists; Weight: " : "Not Exists; Weight: ") << ( g.exists(i, j) ? g.weight(i,j) : 0) << std::endl;
            }
            std::cout << std::endl;
        }
    }
};

int test() {
    graphmatrix<int, int> g;
    g.insert(1);
    g.insert(2);
    g.insert(3);
    g.insert(4);
    g.insert(5);

    g.insert(0,0,0,2);
    g.insert(0,1,0,3);
//    g.insert(0,2,0,1);

    g.insert(1,1,0,1);
//    g.insert(1,2,0,1);

//    g.insert(2,0,0,1);

//    g.insert(3,2,0,1);
    g.insert(3,4,0,1);

    g.insert(4,0,0,1);
    g.insert(4,1,0,3);

    GraphMatrixTravlier<int, int> pg;
    pg(g);


//    g.bfs(0);

//    g.dfs(0);

    auto p = g.tSort(0);
    auto printer = [](int &a) { std::cout << a << "\t"; };
    if (p.empty()) {
        std::cout << "Graph Has Loop" << std::endl;
    } else {
        p.traverse(printer);
    }
}
