//
// Created by 张锐 on 2020/12/3.
//


#include <iostream>
#include "./btree.h"

void vnode(btreenode<int>* p) {
    for (int i = 0; i < p->keys.size(); ++i) {
        printf("visit lcs: \n");
        if (p->childs[i]) vnode(p);
        printf("visit rcs: \n");
        if (p->childs[i+1]) vnode(p);
        printf("visit node %d: \n", p->keys[i]);
    }
};

int test() {
    btree<int> bt;
    std::cout << "Do Search:" << std::endl;
    bt.insert(10);
    bt.insert(20);
    bt.insert(30);
    bt.insert(22);
    bt.insert(45);
    bt.insert(5);
    bt.insert(560);
    bt.insert(33);
    bt.insert(222);
    bt.insert(50);

    std::cout << "Do Insert:";
    auto p = bt.search(10);
    std::cout << 10 << " " << (p ? "Found," : "Not Found,") << (p ? p->keys[p->keys.search(10)] : 0) << std::endl;

    std::cout << "Do Remove:";
    bool r = bt.remove(40);
    if (r) {
        std::cout << " 40 Success!" << std::endl;
    } else {
        std::cout << " 40 Failed!" << std::endl;
    }
    r = bt.remove(50);
    if (r) {
        std::cout << " 50 Success!" << std::endl;
    } else {
        std::cout << " 50 Failed!" << std::endl;
    }
    r = bt.remove(222);
    if (r) {
        std::cout << " 222 Success!" << std::endl;
    } else {
        std::cout << " 222 Failed!" << std::endl;
    }
}
