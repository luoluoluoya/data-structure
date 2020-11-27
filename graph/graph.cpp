//
// Created by 张锐 on 2020/11/27.
//

#include "graph.h"
#include <queue>
#include <stack>
#include <cassert>

template<typename Tv, typename Te>
void graph<Tv,Te>::DFS(int v, unsigned int&clock) {
    status(v) = graphnode<Tv>::discovered; dTime(v) = clock++;
    for (int u = firstNbr (v); -1 < u; u = nextNbr (v, u) ) {
        if ( status(u) == graphnode<Tv>::undiscovered ) {
            type(v, u) = graphedge<Te>::tree;
            parent(u) = v;
            BFS(u, clock);
        } else if ( status(u == graphnode<Tv>::discovered) ) {
            type(v, u) = graphedge<Te>::backword;
        } else {
            type(v, u) = ( dTime(v) < dTime(u) ? graphedge<Te>::froward : graphedge<Te>::cross );
        }
    }
    status(v) = graphnode<Tv>::visited; fTime(v) = clock++;
}

template<typename Tv, typename Te>
void graph<Tv,Te>::BFS(int v, unsigned int&clock) {
    std::queue<int> queue; queue.push(v);
    while ( !queue.empty() ) {
        v = queue.front();  queue.pop();
        status(v) = graphnode<Tv>::discovered; dTime(v) = clock++;
        for (int u = firstNbr (v); -1 < u; u = nextNbr (v, u) ) {
            if ( status(u) == graphnode<Tv>::undiscovered ) {
                type(v, u) = graphedge<Te>::tree;
                parent(u) = v;
                queue.push(u);
            } else {
                type(v, u) = graphedge<Te>::cross; //将(v, u)归类于跨边
            }
        }
        status(v) = graphnode<Tv>::visited;
    }
}

template<typename Tv, typename Te> template<typename PU>
void graph<Tv,Te>::PFS(int v, PU priorityUpdator) {
    priority(v) = 0; status(v) = graphnode<Tv>::visited; parent(v) = -1;
    while (true) {
        //枚举v的所有邻居u, 更新顶点u的优先级及其父顶点
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u))
            priorityUpdator(this, v, u);
        // 找到优先级最高的未访问定点
        for (int minPriority = INT_MAX, i = 0; i < n; ++i)
            if ( status(i) == graphnode<Tv>::discovered && priority(i) < minPriority ) {
                minPriority = priority(i); v = i;
            }
        if ( status(v) == graphnode<Tv>::visited ) break;
        status(v) = graphnode<Tv>::visited;  type( parent(v), v ) = graphedge<Te>::tree;
    }
}

template<typename Tv, typename Te>
bool graph<Tv,Te>::TSort(int v, unsigned int&clock, std::stack<Tv> *nodes) {
    status(v) = graphnode<Tv>::discovered; dTime(v) = clock++;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        if ( status(u) == graphnode<Tv>::undiscovered ) {
             if ( !TSort(u, clock, nodes) ) return false;
        } else if (status(u) == graphnode<Tv>::discovered ) {
            return false;
        }
    }
    status(v) = graphnode<Tv>::visited; fTime(v) = clock++;
    nodes->push(vertex(v));
    return true;
}

// todo
// 利用 fTime 存储当前节点可以通过后向边所能到达的最高祖先节点位置
template<typename Tv, typename Te>
void graph<Tv,Te>::BCC(int v, unsigned int&clock, std::stack<int> &nodes) {
    status(v) = graphnode<Tv>::discovered; dTime(v) = fTime(v) = clock++;
    nodes.push(v);
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        if ( status(u) == graphnode<Tv>::undiscovered ) {
            BCC(u, clock, nodes);
            if ( fTime(u) < dTime(v) )
                fTime(v) = std::min(fTime(v), fTime(u));
            else
                while ( v != nodes.top() ) nodes.pop();
        } else if ( status(u) == graphnode<Tv>::discovered ) {
            if ( u != parent(v) ) fTime(v) = std::min( fTime(v), dTime(u) );  // v 向 u 的后向边。 更新可达到的最高祖先
        }
    }
    status(v) = graphnode<Tv>::visited;
}

template<typename Tv, typename Te>
void graph<Tv,Te>::bfs(int v) {
    assert( 0 <= v && v < n );
    unsigned int clock = 0; int s = v;
    do {
        if ( status(v) == graphnode<Tv>::undiscovered )
            BFS(v,clock);
    } while ( s != ( v = ++v%n ) );
}

template<typename Tv, typename Te>
void graph<Tv,Te>::dfs(int v) {
    assert( 0 <= v && v < n );
    unsigned int clock = 0; int s = v;
    do {
        if ( status(v) == graphnode<Tv>::undiscovered )
            DFS(v,clock);
    } while ( s != ( v = ++v%n ) );
}

template<typename Tv, typename Te>
void graph<Tv,Te>::bcc(int v) {
    assert( 0 <= v && v < n );
    std::stack<int> nodes;
    unsigned int clock = 0; int s = v;
    do {
        if ( status(v) == graphnode<Tv>::undiscovered ) {
            BCC(v,clock, nodes);
            nodes.pop();    // todo
        }
    } while ( s != ( v = ++v%n ) );
}

template<typename Tv, typename Te>
std::stack<Tv>* graph<Tv,Te>::tSort(int v) {
    assert( 0 <= v && v < n );
    std::stack<int> nodes;
    unsigned int clock = 0; int s = v;
    do {
        if ( status(v) == graphnode<Tv>::undiscovered )
            if ( !TSort(v,clock, nodes) ) // 存在环路
                while (!nodes.empty()) nodes.pop();
    } while ( s != ( v = ++v%n ) );
    return nodes;
}

template<typename Tv, typename Te> template<typename PU>
void graph<Tv,Te>::pfs(int v, PU priorityUpdator) {
    assert( 0 <= v && v < n );
    int s = v;
    do {
        if ( status(v) == graphnode<Tv>::undiscovered )
            PFS(v, priorityUpdator);
    } while ( s != ( v = ++v%n ) );
}

template<typename Tv, typename Te>
void graph<Tv,Te>::primPU(int v) {
    reset();
    priority(v) = 0; parent(v) = -1;
    auto priorityUpdator = [](decltype(this) g, int v, int u) {
        if ( g->status(u) == graphnode<Tv>::undiscovered && g->priority(u) > g->weight(v,u) ) {
            g->priority(u) = g->weight(v,u);
            g->parent(u) = v;
            g->type(v, u) = graphedge<Te>::tree;
        }
    };
    pfs(v, priorityUpdator);
}

template<typename Tv, typename Te>
void graph<Tv,Te>::dijkstraPU(int v) {
    reset();
    auto priorityUpdator = [](decltype(this) g, int v, int u) {
        if ( g->status(u) == graphnode<Tv>::undiscovered && g->priority(u) > g->priority(v) + g->weight(v,u) ) {
            g->priority(u) = g->priority(v) + g->weight(v,u);
            g->parent(u) = v;
            g->type(v, u) = graphedge<Te>::tree;
        }
    };
    pfs(v, priorityUpdator);
}

template<typename Tv, typename Te>
void graph<Tv,Te>::bfsPU(int v) {
    auto priorityUpdator = [](decltype(this) g, int v, int u) {
        if ( g->status(u) == graphnode<Tv>::undiscovered && g->priority(u) > g->priority(v) + 1) {
            g->priority(u) = g->priority(v) + 1;
            g->parent(u) = v;
            g->type(v, u) = graphedge<Te>::tree;
        }
    };
    pfs(v, priorityUpdator);
}

template<typename Tv, typename Te>
void graph<Tv,Te>::dfsPU(int v) {
    auto priorityUpdator = [](decltype(this) g, int v, int u) {
        if ( g->status(u) == graphnode<Tv>::undiscovered && g->priority(u) > g->priority(v) - 1) {
            g->priority(u) = g->priority(v) - 1;
            g->parent(u) = v;
            g->type(v, u) = graphedge<Te>::tree;
        }
    };
    pfs(v, priorityUpdator);
}
template<typename Tv, typename Te>
void graph<Tv,Te>::prim(int v) {
    reset(); priority(v) = 0;
    for (int i = 0; i < n; ++i) {
        status(v) = graphnode<Tv>::visited;
        if ( -1 != parent(v) ) type( parent(v), v) = graphedge<Te>::tree;
        for (size_t u = firstNbr(v);  -1 < u; u = nextNbr(v, u)) {
            if ( status(u) == graphnode<Tv>::undiscovered && priority(u) > weight(v, u) ) {
                priority(u) = weight(v, u);
                parent(u) = v;
            }
        }
        for (int min = INT_MAX, u = 0; u < n; u++) {
            if ( status(u) != graphnode<Tv>::undiscovered && priority(u) < min ) {
                v = u;
                min = priority(u);
            }
        }
    }
}

template<typename Tv, typename Te>
void graph<Tv,Te>::dijkstra(int v) {
    reset(); priority(v) = 0;
    for (int i = 0; i < n; ++i) {
        status(v) = graphnode<Tv>::visited;
        if ( -1 != parent(v) ) type( parent(v), v) = graphedge<Te>::tree;
        for (size_t u = firstNbr(v);  -1 < u; u = nextNbr(v, u)) {
            if ( status(u) == graphnode<Tv>::undiscovered && priority(u) > priority(v) + weight(v, u) ) {
                priority(u) = priority(v) + weight(v, u);
                parent(u) = v;
            }
        }
        for (int min = INT_MAX, u = 0; u < n; u++) {
            if ( status(u) != graphnode<Tv>::undiscovered && priority(u) < min ) {
                v = u;
                min = priority(u);
            }
        }
    }
}
