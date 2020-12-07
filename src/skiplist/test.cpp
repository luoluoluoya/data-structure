//
// Created by 张锐 on 2020/12/7.
//

#include "./quadlist.h"
#include "./skiplist.h"

void testQuadList() {
    auto printer = [](int & a) { std::cout << a << " "; };
    quadlist<int> list;
    std::cout << "List Is Empty: " << list.empty() << "; Size: " << list.size() << std::endl;
    std::cout << "Insert As Last: " << list.size() << std::endl;
    list.insertAfterAbove(10, list.last());
    list.insertAfterAbove(20, list.last());
    list.insertAfterAbove(30, list.last());
    list.insertAfterAbove(40, list.last());
    std::cout << "List Is Empty: " << list.empty() << "; Size: " << list.size() << std::endl;
    list.traverse(printer);
}

void testSkipList() {
    skiplist<int, char> sk;
    std::cout << "Skip List Empty: " << sk.empty() << "; Size: " << sk.size() << "; Level: " << sk.level() << std::endl;
    sk.put(0, 'z');
    sk.put(1, 'h');
    sk.put(2, 'a');
    sk.put(3, 'n');
    sk.put(4, 'g');
    std::cout << "Skip List Empty: " << sk.empty() << "; Size: " << sk.size() << "; Level: " << sk.level() << std::endl;

    std::cout << "Skip Trav And Remove! " << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << sk.get(i) << "";
        sk.remove(i);
    }
    std::cout << std::endl;
    std::cout << "Skip List Empty: " << sk.empty() << "; Size: " << sk.size() << "; Level: " << sk.level() << std::endl;
}
