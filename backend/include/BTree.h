#ifndef BTREE_H
#define BTREE_H

class Node {
    public:
            //-----------Constructors / Destructors 

        Node();
        ~Node();
            
            //-----------Getters 

        int getVal(int);
        Node* getChild(int);
        int getSize();
        Node* getParent();

            //-----------Setters 

        void setVal(int,int);
        void setSize(int);
        void setChild(int,Node*);
        void setParent(Node*);

            //-----------Methods 

        bool isLeaf();
        void remove(int);
        int insert(int);
        int getIdx(int);

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
        Node* search(int);
        void remove(int);

    private:
            //-----------Methods 
        void removeAtLeaf(Node*, int);
        void transferFuse(Node*, int);
        void remove(Node*, int);
        void cascade(Node*, Node*, int);
        int sort(int[]);
        void destructor(Node*);
};

#endif
