#include <stdio.h>
#include "BTree.h"
#include <iostream>

int main() {
    BTree btree, btree1;
    btree.insert(15);
    btree.insert(21);
    btree.insert(61);
    btree.insert(37);
    btree.insert(9);
    btree.insert(100);
    btree.insert(3);
    btree.insert(29);
    btree.insert(1);

    btree1.insert(8);
    btree1.insert(30);
    btree1.insert(81);
    btree1.insert(20);
    btree1.insert(56);
    btree1.insert(93);
    btree1.insert(122);
    btree1.insert(46);

    std::cout << ((btree.search(9))? "Test 1 Passed!": "Test 1 Failed!") << std::endl;
    std::cout << ((btree.search(1))? "Test 2 Passed!": "Test 2 Failed!") << std::endl;
    std::cout << ((btree.search(100))? "Test 3 Passed!" : "Test 3 Failed!") << std::endl;
    std::cout << ((btree1.search(122))? "Test 4 Passed!": "Test 4 Failed!") << std::endl;
    std::cout << ((btree1.search(46))? "Test 5 Passed!": "Test 5 Failed!") << std::endl;
    std::cout << ((btree1.search(90))? "Test 6 Failed!" : "Test 6 Passed!") << std::endl;
    std::cout << ((btree1.search(14))? "Test 7 Failed!": "Test 7 Passed!") << std::endl;
    std::cout << ((btree.search(50))? "Test 8 Failed!": "Test 8 Passed!") << std::endl;
    std::cout << ((btree.search(-10))? "Test 9 Failed!" : "Test 9 Passed!") << std::endl;

    return 0;
}
