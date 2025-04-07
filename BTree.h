#ifndef BTREE_H
#define BTREE_H

class Node {
    public:
            //-----------Constructors / Destructors 

        Node();
        ~Node();
            
            //-----------Getters 

        int getVal(int);
        int getSize();
        Node* getChild(int);
        Node* getParent();

            //-----------Setters

        void setVal(int,int);
        void setSize(int);
        void setChild(int,Node*);
        void setParent(Node*);

            //-----------Methods 

        bool isLeaf();
        int insert(int);
    private:
            //-----------Attributes 
        int val[3];
        int size;
        Node* children[4];
        Node* parent;
};

class BTree {
    public:
            //-----------Attributes 

        Node* root;

            //-----------Constructors / Destructors 

        BTree();
        ~BTree();

            //-----------Methods 

        void display();

        void insert(int);
        void remove(int);
        bool search(int);

    private:
            //-----------Methods 
        int sort(int[]);
        void destructor(Node*);
        void cascade(Node*, Node*, int);
};

#endif
