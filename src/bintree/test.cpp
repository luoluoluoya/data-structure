//
// Created by 张锐 on 2020/11/26.
//
#include "bintreenode.h"

int testTreeNode() {
    auto visitor = [](int p) { std::cout << p << " "; };

    bintreenode<int> root(100), lc(50), rc(150), llc(25), lrc(75), rlc(125), rrc(175);
    root.lc = &lc; root.rc = &rc;

    lc.parent = &root; lc.lc = &llc; lc.rc = &lrc;
    rc.parent = &root; rc.lc = &rlc; rc.rc = &rrc;

    llc.parent = &lc; lrc.parent = &lc;
    rlc.parent = &rc; rrc.parent = &rc;

    std::cout << "Root Val: " << root.data << std::endl;
    std::cout << "Traverse By Level: ";
    root.travelLevel(visitor); std::cout << std::endl;
    std::cout << "Zig Lc: ";
    auto p = lc.zig();
    root.travelLevel(visitor); std::cout << std::endl;
    std::cout << "Zag: ";
    p->zag();
    root.travelLevel(visitor); std::cout << std::endl;
    std::cout << "Traverse By Pre: ";
    root.travelPre(visitor);  std::cout << std::endl;
    std::cout << "Traverse By Post: ";
    root.travelPost(visitor); std::cout << std::endl;
    std::cout << "Traverse By In: ";
    root.travelIn(visitor); std::cout << std::endl;
}

int testTree() {
    auto visitor = [](int p) {
        std::cout << p << " ";
    };
    auto printer = [&visitor](bintree<int> &t) {
        std::cout << "Tree Empty: " << t.empty() << "; Size: " << t.size() << "; elements: " << std::endl;
        t.travIn(visitor);  std::cout << std::endl;
    };
    bintree<int> bt;

    auto root = bt.insertAsRoot(100);
    auto lc = bt.insertAsLc(root, 50), rc = bt.insertAsRc(root, 150);
    auto llc = bt.insertAsLc(lc, 25), lrc = bt.insertAsRc(lc, 75);
    auto rlc = bt.insertAsLc(rc, 125), rrc = bt.insertAsRc(rc, 175);
    printer(bt);


    bintree<int> ot;
    auto oo = ot.insertAsRoot(250);
    auto oolc = ot.insertAsLc(oo, 225), oorc = ot.insertAsRc(oo, 275);
    auto oollc = ot.insertAsLc(oolc, 200), oorrc = ot.insertAsRc(oorc, 300);;
    std::cout << "Tree Attach Node oo: " << std::endl;
    printer(ot);
    bt.attachAsRc(rrc, &ot);
    printer(bt);
    printer(ot);
    std::cout << "Tree secede: " << std::endl;
    auto nt = bt.secede(rrc);
    printer(bt);
    printer(*nt);

    std::cout << "Tree Remove: " << std::endl;
    nt->remove(nt->root());
    printer(*nt);
}