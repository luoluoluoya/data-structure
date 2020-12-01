//
// Created by 张锐 on 2020/12/1.
//

#include <iostream>
#include "./avl.h"

int main() {
    auto visitor = [](int p) {
        std::cout << p << " ";
    };
    auto printer = [&visitor](bintree<int> &t) {
        std::cout << "Tree Empty: " << t.empty() << "; Size: " << t.size() << "; elements: " << std::endl;
        t.travIn(visitor);  std::cout << std::endl;
    };

    avl<int>bt;
    std::cout << "insert elements" << std::endl;
    bt.insert(10);
    bt.insert(20);
    bt.insert(30);
    bt.insert(40);
    bt.insert(50);
    bt.insert(60);
    printer(bt);
    std::cout << "remove element" << std::endl;
    bt.remove(10);
    printer(bt);
    std::cout << "search 30";
    auto resu = bt.search(30);
    if (resu) {
        std::cout << " success: " << resu->data << std::endl;
    } else {
        std::cout << " failed! " << std::endl;
    }
    std::cout << "search 100";
    resu = bt.search(100);
    if (resu) {
        std::cout << " success: " << resu->data << std::endl;
    } else {
        std::cout << " failed! " << std::endl;
    }
}
