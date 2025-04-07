#ifndef BTREE_H
#define BTREE_H

class Node {
    public:
        int val[3];
        int size;
        Node* children[4];
        Node* parent;
       
        Node();
        ~Node();

        bool isLeaf();
        int insert(int);
        void insert(Node*, Node*);
};

class BTree {
    public:
        Node* root;

        BTree();
        ~BTree();
        void insert(int);
        void remove(int);
        bool search(int);

    private:
        void sort(int[]);
        void destructor(Node*);
        void cascade(Node*, Node*, Node*, int);
};

#endif
