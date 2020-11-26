//
// Created by 张锐 on 2020/11/25.
//

#include <iostream>
#include "src/stack/stack.cpp"
#include "src/vector/vector.cpp"


int test() {
    stack<int> s;
    std::cout << "Size: " << s.size() << "; Empty: " << s.empty() << std::endl;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    std::cout << "Pop: " << s.pop() << std::endl;
    std::cout << "Size: " << s.size() << "; Empty: " << s.empty() << std::endl;
    std::cout << "Pop: " << s.pop() << std::endl;
    std::cout << "Pop: " << s.pop() << std::endl;
    std::cout << "Top: " << s.top() << std::endl;
    std::cout << "Size: " << s.size() << "; Empty: " << s.empty() << std::endl;
}
