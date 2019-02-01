#ifndef AVL_H
#define AVL_H

#include "node.h"

class AVL
{
    private:
        Node* root;

        int height(Node*);
        void doRotations(Node* &,bool);
        void leftRotation(Node* &);
        void rightRotation(Node* &);
        void leftRightRotation(Node* &);
        void rightLeftRotation(Node* &);

    public:
        AVL(){root = NULL;}
        ~AVL(){delete root;}

        void insertNode(Interval val);
        void insertNodeRecursively(Node*&,int);
        void inorder(Node*);
        Node* getRoot(){return root;}
        void pathToRoot(Interval val);
        void breadthFirst(Node*);
        void deleteNode(Interval val);
        Node* findNode(Interval val);
};


#endif // AVL_H
