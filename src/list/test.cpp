//
// Created by 张锐 on 2020/11/25.
//

#include <iostream>
#include "src/list/listnode.cpp"
#include "src/list/list.cpp"

template<typename T>
void listPrinter(list<T> &l) {
    auto traver = [](typename list<T>::pointer p) { std::cout << p->data << "  "; };
    std::cout << "Print List, empty: " << l.empty() << "; size: " << l.size() << std::endl;
    l.traverse(traver); std::cout << std::endl;
}

int test() {
    std::cout << "=================== START TEST LIST ===================" << std::endl;
    list<int> l1;
    std::cout << "Insert Elements: ";
    l1.insertFront(1);
    l1.insertFront(2);
    l1.insertFront(3);
    l1.insertFront(4);
    l1.insertBack(9);
    l1.insertBack(8);
    l1.insertBack(7);
    l1.insertBack(6);
    listPrinter(l1);

    listnode<int>::pointer p = l1.front()->succ;
    std::cout << "Pointer P Value: " << p->data << std::endl;
    l1.insertB( p, 50 );
    l1.insertA( p, 100 );
    listPrinter(l1);

    std::cout << "Access Element: " << std::endl;
    std::cout << "Front: " << l1.front()->data << std::endl;
    std::cout << "Back: " << l1.back()->data << std::endl;
    std::cout << "l1[4]: " << l1[4]->data << std::endl;
    std::cout << "l1[6]: " << l1[6]->data << std::endl;
    //std::cout << "l1[6]: " << l1[100]->data << std::endl; //error

    std::cout << "Remove Pointer P: " << l1.remove(p) << std::endl;
    l1.front()->data = 200;
    l1.back()->data  = 200;
    listPrinter(l1);

    std::cout << "List Algorithm: " << std::endl;
    p = l1.find(200);
    std::cout << "find 200: " << ( p ? p->data : INT_MIN) << std::endl;
    std::cout << "Has Sorted: " << l1.disordered() << std::endl;
    std::cout << "Do duplicate: "  << std::endl;
    l1.duplicate();
    listPrinter(l1);
    std::cout << "Do Reverse: " << std::endl;
    l1.reverse();
    listPrinter(l1);

    std::cout << "Do Sorting: " << std::endl;
    l1.sort();
    listPrinter(l1);

    std::cout << "Copy Construct: " << std::endl;
    list<int> l2(l1);
    listPrinter(l2);

    std::cout << "=================== END TEST LIST ===================" << std::endl;
}
