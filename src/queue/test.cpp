//
// Created by 张锐 on 2020/11/25.
//

#include <iostream>
#include "src/list/list.cpp"
#include "src/list/listnode.cpp"
#include "src/queue/queue.cpp"


int main() {
    auto printer = [](const queue<int> &q) { std::cout << "queue empty: " << q.empty() <<  "; size: " << q.size() << std::endl; };
    queue<int> q;
    printer(q);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    printer(q);

    std::cout << "deque: " << q.dequeue() << std::endl;
    std::cout << "deque: " << q.dequeue() << std::endl;
    std::cout << "deque: " << q.dequeue() << std::endl;

    printer(q);
    std::cout << "front: " << q.front() << std::endl;
    q.front() = 100;
    std::cout << "front: " << q.front() << std::endl;
}
