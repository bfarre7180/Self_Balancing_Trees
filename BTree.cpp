#include "BTree.h"
#include <iostream>
#include <queue>

//--------------------------------------Node Class---------------------------------------------------------
//------------Constructor---------------
Node::Node() : size(0), parent(nullptr) {
    for(int i = 0; i < 4; i++){children[i] = nullptr;}
}

//------------Getters-------------------
int Node::getVal(int idx) {
    if(idx >= 0 && idx < 3) {
        return val[idx];
    }
    return -1;
}
Node* Node::getChild(int idx) {
    if(idx >= 0 && idx < 4) {
        return children[idx];
    }
    return nullptr;
}
int Node::getSize() {return size;}
Node* Node::getParent() {return parent;}

//------------Setters-------------------
void Node::setVal(int idx, int value) {
    if(idx >= 0 && idx < 3) {
        val[idx] = value;
    }
}
void Node::setSize(int s) {
    if(s >=0 && s <= 3) {
        size = s;
    }
}
void Node::setChild(int idx, Node* node) {
    if(idx >= 0 && idx < 4) {
        children[idx] = node;
    }
}
void Node::setParent(Node* node) {parent = node;}

//------------Methods-------------------
bool Node::isLeaf(){
return children[0] == nullptr && children[1] == nullptr && children[2] == nullptr && children[3] == nullptr;
}

int Node::insert(int value) {
    if(size == 3) {
        return -1;
    }
    int i = 0;
    while(i < size) {
        if(value < val[i]) {
            for(int j = size; j > i; j--) {
                val[j] = val[j-1];
            }
            break;
        }
        i++;
    }
    val[i] = value;
    size++;
    return i;
            //[1,2,3], size = 2, insert 2, i = 1
}

//------------Destructor----------------
Node::~Node() {
    for(int i = 0; i < 4; i++){children[i] = nullptr;}
}

//--------------------------------------BTree Class-----------------------------------------------------------
//------------Constructor---------------
BTree::BTree() : root(nullptr) {}

void BTree::display() {
    if(root == nullptr) {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    int level = 0;
    while(!q.empty()) {
        Node* curr = q.front();
        q.pop();
        std::cout << "--";
        for(int i = 0; i < curr->getSize(); i++) {
            std::cout << curr->getVal(i) << "--";
            if(!curr->isLeaf()) {
                q.push(curr->getChild(i));
            }
        }
        if(!curr->isLeaf()) {
            q.push(curr->getChild(curr->getSize()));
        }
        if(curr->getParent() != nullptr) {
            std::cout << "\tParent is: " << curr->getParent()->getVal(0);
        }
        std::cout << std::endl;
    }
}

void BTree::insert(int value) {
    if(root == nullptr) {
        root = new Node();
        root->insert(value);
        return;
    }
    Node* temp = root;
    while (!temp->isLeaf()) {
        for(int i = 0; i < temp->getSize()+1; i++) {
            if(i == temp->getSize() || value < temp->getVal(i)) {
                temp = temp->getChild(i);
                break;
            }
        }
    }
    if(temp->insert(value) == -1) {
        cascade(temp, nullptr, value);
    }
}

bool BTree::search(int value) {
    Node* temp = root;
    while(temp != nullptr) {
        for(int i = 0; i < temp->getSize()+1; i++) {
            if(i == temp->getSize() || value < temp->getVal(i)) {
                temp = temp->getChild(i);
                break;
            } else if(value == temp->getVal(i)) {
                return true;
            }
        }
    }
    return false;
}

void BTree::remove(int value){}

BTree::~BTree() {
    destructor(root);
    root = nullptr;
}

//When cascading there are 3 possibilites 
// 1: The cascading node's parent can accept the value i.e it won't be overflowing 
//      What we can do here is push up the third element and split up the node accordingly and directly assign the pointers from the parent node 
//  2: The cascading node it the root 
// 3: The cascade goes up indefinately 
void BTree::cascade(Node* curr, Node* child, int value){
    //CASE 1 (Also base case for the recursion) 
    if(curr->getSize() < 3) {
        int index = curr->insert(value);
        for(int i = curr->getSize(); i > index+1; i--) {
            curr->setChild(i, curr->getChild(i-1));
        }
        curr->setChild(index+1, child);

        return;
    }

    int values[4];
    values[0] = value, values[1] = curr->getVal(0), values[2] = curr->getVal(1), values[3] = curr->getVal(2);
    int idx = sort(values);

    curr->setVal(0, values[0]), curr->setVal(1, values[1]), curr->setSize(2);
    Node* temp = new Node();
    temp->insert(values[3]);

    //We want to align the children in the correct order since curr size == 2, it should have 3 children, and the last child (curr->children[3]) should go to temp 
    if(idx == 0) {
        temp->setChild(1, curr->getChild(3));
        temp->setChild(0, curr->getChild(2));
        curr->setChild(2, curr->getChild(1));
        curr->setChild(1, child);
    } else if (idx == 1) {
        temp->setChild(1, curr->getChild(3));
        temp->setChild(0, curr->getChild(2));
        curr->setChild(2, child);
    } else if(idx == 2) {
        temp->setChild(1, curr->getChild(3));
        temp->setChild(0, child);
    } else if(idx == 3) {
        temp->setChild(1, child);
        temp->setChild(0, curr->getChild(3));
    }

    curr->setChild(3, nullptr);

    //Also dont forget to change the parent pointers of the children Nodes 
    if(child != nullptr) {
        curr->getChild(0)->setParent(curr);
        curr->getChild(1)->setParent(curr);
        curr->getChild(2)->setParent(curr);
        temp->getChild(0)->setParent(temp);
        temp->getChild(1)->setParent(temp);
    }

    //CASE 2 
    if(curr->getParent() == nullptr) {
        curr->setParent(new Node());
        curr->getParent()->setChild(0, curr);
        root = curr->getParent();
    }
    temp->setParent(curr->getParent());
    //CASE 3 
    cascade(curr->getParent(), temp, values[2]);
}

int BTree::sort(int values[4]) {
    for(int i = 0; i < 3; i++) {
        if(values[i] < values[i+1]) {
            return i;
        }
        values[i] ^= values[i+1];
        values[i+1] ^= values[i];
        values[i] ^= values[i+1];
    }
    return 3;
}


void BTree::destructor(Node* curr) {
    if(curr == nullptr) {return;}
    if(!curr->isLeaf()) {
        for(int i = 0; i < curr->getSize() + 1; i++) {
            destructor(curr->getChild(i));
        }
    }
    delete curr;
}
