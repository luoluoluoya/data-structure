//
// Created by 张锐 on 2020/11/30.
//

#include <iostream>
#include "./bst.h"

int test() {
    auto visitor = [](int p) {
        std::cout << p << " ";
    };
    auto printer = [&visitor](bintree<int> &t) {
        std::cout << "Tree Empty: " << t.empty() << "; Size: " << t.size() << "; elements: " << std::endl;
        t.travIn(visitor);  std::cout << std::endl;
    };

    bst<int>bt;
    bt.insert(10);
    bt.insert(20);
    bt.insert(30);
    bt.insert(40);
    bt.insert(50);
    bt.insert(60);
    printer(bt);

    int i = 24;
    bst<int>::node_pointer p = bt.search(i);
    std::cout << "Search i: " << (p ? p->data : 0) << std::endl;

    if (!p) {
        auto p1 = bt.insert(i);
        if (p1.second) {
            std::cout << "Insert i success: " << p1.first->data << std::endl;
        } else {
            std::cout << "Insert i error: " << p1.first->data << std::endl;
        }
    }

    p = bt.search(i);
    if (p) {
        std::cout << "Search i: Exists " << p->data << std::endl;
    }
    auto p1 = bt.insert(i);
    if (p1.second) {
        std::cout << "Insert i again success: " << p1.first->data << std::endl;
    } else {
        std::cout << "Insert i again error: " << p1.first->data << std::endl;
    }

    printer(bt);
    bool removed = bt.remove(i);
    std::cout << "Remove i: " << (removed ? "successed" : "failed") << std::endl;

    removed = bt.remove(i);
    std::cout << "Remove i again: " << (removed ? "successed" : "failed") << std::endl;

    printer(bt);
}
