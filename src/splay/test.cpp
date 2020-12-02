//
// Created by 张锐 on 2020/12/2.
//

#include <iostream>
#include "./src/bintree/bintree.h"
#include "./src/bintree/bintree.cpp"
#include "./src/bst/bst.cpp"
#include "./src/bintree/bintreenode.h"
#include "./src/bintree/bintreenode.cpp"
#include "./src/splay/splay.h"
#include "./src/splay/splay.cpp"

int test() {
    auto visitor = [](int p) {
        std::cout << p << " ";
    };
    auto printer = [&visitor](splay<int> &t) {
        std::cout << "Tree Empty: " << t.empty() << "; Size: " << t.size() << "; elements: " << std::endl;
        t.travIn(visitor);  std::cout << std::endl;
    };

    splay<int> st;
    st.insert(30);
    st.insert(14);
    st.insert(20);
    st.insert(5);
    st.insert(2);
    st.insert(100);
    std::cout << "Doing Insert: " << std::endl;
    printer(st);
    std::cout << "Doing Remove: " << std::endl;
    st.remove(20);
    st.remove(10);
    st.remove(2);
    printer(st);
    std::cout << "Doing Search: " << std::endl;
    auto p = st.search(14);
    std::cout << "Search 14: " << p->data <<  std::endl;
    p = st.search(100);
    std::cout << "Search 100: " << p->data <<  std::endl;
    p = st.search(20);
    std::cout << "Search 20: " << p->data <<  std::endl;
}
