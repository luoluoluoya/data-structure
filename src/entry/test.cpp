//
// Created by 张锐 on 2020/12/3.
//

#include "entry.h"

int test() {
    entry<int, int> e1(10,20), e2(10,30), e3(11,120), e4(12,120), e5(12,120);
    std::cout << "e1=e2:" << (e1 == e2) << std::endl;
    std::cout << "e1=e3:" << (e1 == e3) << std::endl;
    std::cout << "e1=e4:" << (e1 == e4) << std::endl;
    std::cout << "e1=e5:" << (e1 == e5) << std::endl;

    std::cout << "e2=e3:" << (e2 == e3) << std::endl;
    std::cout << "e2=e4:" << (e2 == e4) << std::endl;
    std::cout << "e2=e5:" << (e2 == e5) << std::endl;

    std::cout << "e3=e4:" << (e3 == e4) << std::endl;
    std::cout << "e3=e5:" << (e3 == e5) << std::endl;

    std::cout << "e4=e5:" << (e4 == e5) << std::endl;


    std::cout << "e1<e2:" << (e1 < e2) << std::endl;
    std::cout << "e1<e3:" << (e1 < e3) << std::endl;
}