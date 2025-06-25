#include<iostream>
#include<stdio.h>
#include "BTree.h"

static int passed;

int main() {
    std::cout << "Welcome to the BTree/RBTree Testbed, there are currently 11 total Methods to be tested" << std::endl;
    BTree* test = new BTree();
    //-------Test 1------
    std::cout << "--------------Test #1----------------" << std::endl;
    test->insert(5);
    test->insert(10);
    test->insert(40);
    test->insert(15);
    test->insert(90);
    test->insert(41);
    test->insert(99);
    test->insert(33);
    test->insert(95);
    test->insert(21);
    test->insert(12);
    test->insert(46);
    test->insert(65);
    test->insert(36);
    test->insert(31);
    test->insert(84);
    test->insert(58);
    test->insert(49);
    test->insert(83);

    if((test->root->getVal(0) == 40)) {
        std::cout << "40 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "40 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(0)->getVal(0) == 15) {
        std::cout << "15 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "15 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(0)->getVal(1) == 33) {
        std::cout << "33 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "33 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(1)->getVal(0) == 49) {
        std::cout << "49 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "49 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(1)->getVal(1) == 65) {
        std::cout << "65 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "65 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(1)->getVal(2) == 90) {
        std::cout << "90 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "90 is in the wrong spot, Test Failed" << std::endl;
    }
    if(test->root->getChild(0)->getChild(0)->getVal(0) == 5) {
        std::cout << "5 is in the right spot, Test Passed" << std::endl;
    } else {
        std::cout << "5 is in the wrong spot, Test Failed" << std::endl;
    }

    std::cout << "\n\n----------------ORIGINAL TREE----------------" << std::endl;
    test->display();

    std::cout << "\n\n------------Tree After Removing 10-----------" << std::endl;
    test->remove(10);
    test->display();

    std::cout << "\n\n------------Tree After Removing 36-----------" << std::endl;
    test->remove(36);
    test->display();

    std::cout << "\n\n------------Tree After Removing 40-----------" << std::endl;
    test->remove(40);
    test->display();

    std::cout << "\n\n------------Tree After Removing 65-----------" << std::endl;
    test->remove(65);
    test->display();

    std::cout << "\n\n-----Tree After Removing a # not in tree-----" << std::endl;
    test->remove(400);
    test->display();

    //std::cout << "\n\n------------Tree After Removing 40-----------" << std::endl;
    //test->remove(40);
    //test->display();

    delete(test);
}

