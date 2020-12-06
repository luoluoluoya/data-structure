//
// Created by 47302 on 2020/12/6.
//

#include "./complete_binary_heap.h"
#include "./leftheap.h"

int compHeap() {
    int arr[] = {10,20,7,2,5,1,100};
    CompleteBinaryHeap<int> pq(arr, sizeof(arr)/sizeof(int ));
    std::cout << "PQ size: " << pq.size() << std::endl;
    while (pq.size()) {
        std::cout << "PQ Current Max: " << pq.delMax() << std::endl;
    }
    std::cout << "PQ IS Empty!" << std::endl;
}


int testLeftHeap() {
#include <iostream>
#include "priorityqueue/complete_binary_heap.h"
#include "priorityqueue/complete_binary_heap.cpp"
#include "bintree/bintree.cpp"
#include "bintree/bintreenode.cpp"
#include "priorityqueue/leftheap.h"
#include "priorityqueue/leftheap.cpp"
#include "vector/vector.cpp"

    int main() {
        LeftHeap<int> lh1;
        lh1.insert(10);
        lh1.insert(7);
        lh1.insert(6);
        lh1.insert(8);
        lh1.insert(3);
        lh1.insert(9);
//    std::cout << "PQ1 SIze: " << lh1.size() << std::endl;
//    while (lh1.size())
//        std::cout << "PQ1 Current Max Value: " << lh1.delMax() << std::endl;
//    std::cout << "PQ1 Empty!" << lh1.size() << std::endl;

        LeftHeap<int> lh2;
        lh1.insert(20);
        lh1.insert(30);
        lh1.insert(23);
        lh1.insert(27);
        lh1.insert(21);
//    std::cout << "PQ2 SIze: " << lh1.size() << std::endl;
//    while (lh1.size())
//        std::cout << "PQ2 Current Max Value: " << lh1.delMax() << std::endl;
//    std::cout << "PQ2 Empty!" << lh1.size() << std::endl;
        lh1.merge(lh2);

        std::cout << "Do Merged !" << std::endl;
        std::cout << "lh1 size:" << lh1.size() << "; lh2 size:" << lh2.size() << std::endl;
        while (lh1.size())
            std::cout << "PQ1 Current Max Value: " << lh1.delMax() << std::endl;
        std::cout << "PQ1 Empty!" << lh1.size() << std::endl;
    }
}