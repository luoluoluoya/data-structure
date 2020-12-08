//
// Created by 张锐 on 2020/12/7.
//

#include "./hashtable.h"

int test() {
    HashTable<int, char> table;
    std::cout << "HashTable Size: " << table.size() << std::endl;
    table.put(0, 'z');
    table.put(1, 'h');
    table.put(2, 'a');
    table.put(3, 'n');
    table.put(4, 'g');
    std::cout << "HashTable Size: " << table.size() << std::endl;

    std::cout << "Skip Trav And Remove! " << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << table[i] << "";
        table.remove(i);
    }
    std::cout << std::endl;
    std::cout << "HashTable Size: " << table.size() << std::endl;

    std::cout << "Insert By []: " << std::endl;
    table[0] = 'z';
    table[1] = 'h';
    table[2] = 'a';
    table[3] = 'n';
    table[4] = 'g';
    std::cout << "Skip Trav And Remove! " << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << table[i] << "";
        table.remove(i);
    }
    std::cout << std::endl;
    std::cout << "HashTable Size: " << table.size() << std::endl;
}