#include <iostream>
#include "vector.h"


int test() {
    auto print = [](const int*p) { std::cout << *p << " "; };

    vector<int> vec(0);
    vec.insert(11);
    vec.insert(4);
    vec.insert(8);
    vec.insert(2);
    vec.insert(1);

    std::cout << "Unsorted:  ";
    vec.traverse(print);     std::cout << std::endl;
    std::cout << "Find 4: " << vec.find(4) << std::endl;
    std::cout << "Find 6: " << vec.find(6) << std::endl;

    std::cout << "Do Sorted: ";
    // 1 2 4 8 11
    vec.sort();
    vec.traverse(print);     std::cout << std::endl;
    std::cout << "Search 4: " << vec.search(4) << std::endl;
    std::cout << "Search 6: " << vec.search(6) << std::endl;

    std::cout << "Vector Info: ";
    std::cout << "capacity: " << vec.capacity() << "; size: " << vec.size() << std::endl;
    int e = vec.remove(4);
    std::cout << "Remove " << e << "; capacity: " << vec.capacity() << "; size: " << vec.size() << std::endl;
    e = vec.remove(3);
    std::cout << "Remove " << e << "; capacity: " << vec.capacity() << "; size: " << vec.size() << std::endl;
    e = vec.remove(2);
    std::cout << "Remove " << e << "; capacity: " << vec.capacity() << "; size: " << vec.size() << std::endl;
    e = vec.remove(1);
    std::cout << "Remove " << e << "; capacity: " << vec.capacity() << "; size: " << vec.size() << std::endl;

    std::cout << "Do UnSorted: ";
    vec.unsort();
    vec.traverse(print);     std::cout << std::endl;

    std::cout << "Do Insert: ";
    vec.insert(10);
    vec.insert(10);
    vec.insert(120);
    vec.insert(30);
    vec.insert(12);
    vec.insert(30);
    vec.insert(3);
    vec.traverse(print);     std::cout << std::endl;
    std::cout << "Deduplicate :";
    vec.deduplicate();
    vec.traverse(print);     std::cout << std::endl;

    vec.insert(30);
    vec.insert(120);
    vec.insert(120);
    vec.sort();
    std::cout << "Sorted Vector :";
    vec.traverse(print);     std::cout << std::endl;
    std::cout << "Uniquify :";
    vec.uniquify();
    vec.traverse(print);     std::cout << std::endl;

    // 【】/at
    std::cout << "At 3: " << *vec.at(3) << std::endl;
    *vec[3] = 100;
    std::cout << "[3]: "<< *vec[3] << std::endl;

    vector<int> vec1(vec), vec2;
    std::cout << "Copy Construct :"; vec1.traverse(print);  std::cout << std::endl;

    vec2 = vec1;
    std::cout << "Copy Operator = :"; vec2.traverse(print);  std::cout << std::endl;
}
