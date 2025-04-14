#include "BTree.h"
#include <iostream>
#include <queue>

//--------------------------------------Node Class---------------------------------------------------------------------------------------------------
//------------Constructor / Destructor-------------------------- 
Node::Node() : size(0), parent(nullptr) {
    for(int i = 0; i < 4; i++){children[i] = nullptr;}
}
Node::~Node() {
    for(int i = 0; i < 4; i++){children[i] = nullptr;}
}

//------------Getters------------------------------------------- 
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

//------------Setters------------------------------------------- 
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

//------------Methods------------------------------------------- 
bool Node::isLeaf(){
return children[0] == nullptr && children[1] == nullptr && children[2] == nullptr && children[3] == nullptr;
}

void Node::remove(int value) {
    for(int i = 0; i < size; i++) {
        if(val[i] == value) {
            for(int j = i; j < size-1; j++) {
                val[j] = val[j+1];
            }
            size--;
            break;
        }
    }
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

int Node::getIdx(int value) {
    for(int i = 0; i < size; i++) {
        if(value < val[i]) {
            return i;
        }
    }
    return size;
}



//--------------------------------------BTree Class--------------------------------------------------------------------------------------------------
//------------Constructor / Destructor-------------------------- 
BTree::BTree() : root(nullptr) {}
BTree::~BTree() {
    destructor(root);
    root = nullptr;
}


//------------Methods------------------------------------------- 
void BTree::display() {
    if(root == nullptr) {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
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

Node* BTree::search(int value) {
    Node* temp = root;
    while(temp != nullptr) {
        for(int i = 0; i < temp->getSize()+1; i++) {
            if(i == temp->getSize() || value < temp->getVal(i)) {
                temp = temp->getChild(i);
                break;
            } else if(value == temp->getVal(i)) {
                return temp;
            }
        }
    }
    return nullptr;
}

//When deleting an element there are Quite a bit of possibilites, the easiest one is when the size of the node is > 1 
void BTree::remove(int value){
    Node* toDel = search(value);
    if(toDel == nullptr || toDel->getSize() < 1) {  //Error Handling 
        std::cout << "Error trying to delete, node is either nullptr (value not found), or size is < 1" << std::endl;
        return;
    }

    toDel->isLeaf()? removeAtLeaf(toDel, value): remove(toDel, value);
}

void BTree::removeAtLeaf(Node* del, int value) {
    if(del == nulptr || del->getSize < 1) {  //Error Handling 
        std::cout << "Error, del is nullptr or size < 1" << std::endl;
        return;
    }

    if(del->getSize() > 1) { //Easy Case 
        del->remove(value);
        return;
    }
    if(root == del) {  //Gotta check there is a parent node first 
        root->remove(value);
        delete(root);
        return;
    }

    Node* parent = del->getParent();

    //Need to swap and transfer 
    int idx = parent->getIdx(value);
    int left = (idx > 0)? parent->getChild(idx-1)->getSize() : -1;
    int right = (idx < parent->getSize())? parent->getChild(idx+1)->getSize() : -1;

    if(left > 1) {
        value = parent->getChild(idx-1)->getVal(left-1);
        del->setVal(0, parent->getVal(idx-1));
        parent->setVal(idx-1, value);
        parent->getChild(idx-1)->remove(value);
        return;
    }
    if(right > 1) {
        value = parent->getChild(idx+1)-getVal(0);
        del->setVal(0,parent->getVal(idx));
        parent->setVal(idx, value);
        parent->getChild(idx+1)->remove(value);
        return;
    }
    //Sibling nodes are both size 1 which means that we need to swap and fuse but we also have to check if the parent node has more than 1 val or else it will be empty 

    transferFuse(del, value);
}

// All we know is that the sibling nodes are both size 1 and that the parent may or may not be size 1 as well 
void BTree::transferFuse(Node* del, int value) {
    if(del->getSize() > 1) { // Base case for the recursion 
        del-remove(value);
        return;
    }
    if(del == root) {  // Error handling 
        std::cout << "Error root is trying to be deleted when there are more elements in the BTree" << std::endl;
        return;
    }

}

// Much like BST's we need to go down either the right subtree and look for the element farthest to the left and swap it with the value we want 
// deleted, or go down the left subtreee and look for the farthest element in the right, either way this means the element we will swap will be 
// a leaf node, in order to make it seemingly random so one side isn't 'heavier' than the other 
void BTree::remove(Node* del, int value) {
    if(del->isLeaf()) { // Error Handling 
        std::cout << "Error del is a leaf for some reason" << std::endl;
        return;
    }
    int idx = 0, swap = 0;
    Node* temp = del;
    for(int i = 1; i < del->getSize(); i++) {
        if(value == del->getVal(i)) {
            idx = i;
            break;
        }
    }
    if(value % 2 == 0) {  // We will be going to the left subtree 
        temp = temp->getChild(idx);
        while(!temp->isLeaf()) {temp = temp->getChild(temp->getSize());}
        swap = temp->getVal(temp->getSize()-1);
        temp->setVal(temp-getSize()-1, value);
    } else { // We will be going into the right subtree 
        temp = temp->getChild(idx+1);
        while(!temp->isLeaf()) {temp = temp->getChild(0);}
        swap = temp->getVal(0);
        temp->setVal(0,value);
    }
    del->setVal(idx, swap);
    removeAtLeaf(temp, value);
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
