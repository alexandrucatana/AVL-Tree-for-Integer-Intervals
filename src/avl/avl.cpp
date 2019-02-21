#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <stdio.h>
#include "avl.h"

using namespace std;


Node* AVL::findNode(Interval val)
{
    Node* someNode = getRoot();

    queue<Node*> q;

    q.push(someNode);

    while (!q.empty())
    {
        someNode = q.front();
        q.pop();

        if(someNode->value.compareTo(val) == 0)
            return someNode;

        if (someNode->left != NULL)
            q.push(someNode->left);

        if (someNode->right != NULL)
            q.push(someNode->right);
    }

    return someNode;
}


void AVL::breadthFirst(Node* someNode)
{
    queue<Node*> q;

    q.push(someNode);
    while (!q.empty())
    {
        someNode = q.front();
        q.pop();
        std::cout << someNode->value.printInterval();

        // TODO: log all cout this information
        if(someNode->left != NULL && someNode->left->left == someNode)
            cout << "ERROR LEFT" << endl;

        if(someNode->right != NULL && someNode->right->right == someNode)
            cout << "ERROR RIGHT" << endl;

        if (someNode->left != NULL)
            q.push(someNode->left);

        if (someNode->right != NULL)
            q.push(someNode->right);
    }
}


void AVL::leftRotation(Node* &someNode)
{
    Node* aux = someNode;
    someNode = someNode->right;

    if(aux->parent) //set new parent for someNode
        someNode->parent = aux->parent;

    aux->right = someNode->left;

    if(someNode->left)
    {
        //someNode->left->parent = aux->right;//set parent for someNode->left
        someNode->left->parent = aux;//set parent for someNode->left
    }
    someNode->left = aux;

    if(aux == root)
    {
        root = someNode;
        root->parent = NULL;
        aux->parent = someNode; // set new parent for aux
    }
    else
    {
        if(aux->parent->right == aux)
            aux->parent->right = someNode;
        else
            aux->parent->left = someNode;

        aux->parent = someNode;
    }

}

void AVL::rightRotation(Node* &someNode)
{
    Node* aux = someNode;
    someNode = someNode->left;

    if(aux->parent) //set new parent for someNode
        someNode->parent = aux->parent;

    aux->left = someNode->right;

    if(someNode->right)
    {
        //someNode->right->parent = aux->left;//set parent for someNode->left
        someNode->right->parent = aux;//set parent for someNode->left
    }

    someNode->right = aux;

    if(aux == root)
    {
        root = someNode;
        root->parent = NULL;
        someNode->parent = NULL;
        aux->parent = someNode; // set new parent for aux

        // TODO: remove this in the future
        //breadthFirst(root);
        cout << endl;

    }
    else
    {
        if(aux->parent->right == aux)
        {
            aux->parent->right = someNode;
        }
        if(aux->parent->left == aux)
        {
            aux->parent->left = someNode;
        }
        aux->parent = someNode;
    }
}

void AVL::leftRightRotation(Node* &someNode)
{
    leftRotation(someNode->left);
    rightRotation(someNode);
}

void AVL::rightLeftRotation(Node* &someNode)
{
    rightRotation(someNode->right);
    leftRotation(someNode);
}

int AVL::height(Node* someNode)
{
    if (someNode == NULL)
        return 0;
    else
    {
        if(height(someNode->right) > height(someNode->left))
            return 1 + height(someNode->right);
        return 1 + height(someNode->left);
    }
}


void AVL::deleteNode(Interval val)
{
    Node* p;
    Node* q;
    Node* r;
    Node* balanceCheck;

    if(root->value.compareTo( val) == 0)
    {

        if(root->left && root->right == NULL)
        {
            // Delete Root, case 1\n";
            p = root;
            root = root->left;
            delete p;
        }
        else if(root->right && root->left == NULL)
        {
            // Delete Root, case 2\n";

            p = root;
            root = root->right;
            delete p;
        }
        else if(root->right == NULL  && root->left == NULL)
        {
            // "Delete Root, case 3\n";
            // NULL TREE\n";
            delete root;
        }
        else
        {
            // Delete Root, case 4\n";

            p = root;
            p = p->right;

            if(p->left) //p has at least one left son
            {
                // There is A LEFT SON\n";
                while(p->left)
                {
                    p = p->left;
                    p->value.printInterval();
                }

                root->value = p->value;

                if(p->right) //the inorder predecessor might have a right son
                {
                    balanceCheck = p->right;
                    p->right->parent = p->parent;
                    p->parent->left = p->right;
                }
                else
                {
                    balanceCheck = p->parent;
                    p->parent->left = NULL;
                    p->parent = NULL;
                }
                delete p;

                // Left son, BALANCE CHECK by balanceCheck->value.printInterval();
                doRotations(balanceCheck,1);

            }
            else //p has no left son
            {

                // No Left Son, Replace with "  p->value.printInterval() << endl;
                root->value = p->value;
                p->parent = NULL;

                if(p->right)
                {
                    // No Left son, in if statement"
                    root->right = p->right;
                    p->right->parent = root;
                    // balanceCheck = root->right;
                    // "No Left son, in if statement BALANCE CHECK :  " << balanceCheck->value.printInterval();
                }
                else
                {
                    root->right = NULL;
                    balanceCheck = root;
                }

                delete p;

                // No Left son, BALANCE CHECK :  " << balanceCheck->value.printInterval();
                // Remove this in the future
                if(balanceCheck->parent)
                    cout << "No Left son, BALANCE CHECK parent:  " << balanceCheck->parent->value.printInterval();

                doRotations(balanceCheck,1);
            }
        }
    }
    else
    {
        p = findNode(val);

        if(p->value.compareTo(val) == 0)
        {
            if(p->left && p->right == NULL)
            {
                //only left son
                q = p;
                q = q->left;

                if(p->parent->right == p)
                {
                    // NODE HAS LEFT ONE SON ONLY CASE 1\n";
                    p = p->parent;
                    p->right = q;
                    q->parent = p;
                }
                else
                {
                    // NODE HAS LEFT ONE SON ONLY CASE 2\n";
                    r = p;
                    p = p->parent;

                    p->left = q;
                    q->parent = p;

                    delete r;
                }

            }
            else if(p->right && p->left == NULL)
            {
                //only right son
                q = p;
                q = q->right;

                if(p->parent->left == p)
                {
                    // Debugging: remove
                    cout << "NODE HAS LEFT SON ONLY CASE 1\n";

                    p = p->parent;
                    p->left = q;
                    q->parent = p;
                }
                else
                {
                    // NODE HAS LEFT SON ONLY CASE 2\n";
                    r = p;
                    p = p->parent;

                    p->right = q;
                    q->parent = p;

                    delete r;
                }
            }
            else if(p->right == NULL  && p->left == NULL)
            {
                //Leaf : Left Case\n";
                if(p->parent->right == p)
                {
                    p->parent->right = NULL;
                    p->parent = NULL;
                    delete p;
                }
                else
                {
                    p->parent->left = NULL;
                    p->parent = NULL;
                    delete p;
                }
            }
            else
            {
                //two sons: replace node with its inorder predecessor
                q = p;
                q = p->right;

                if(q->left)
                {
                    while(q->left)
                        q = q->left;

                    p->value = q->value;

                    if(q->right) //nasty case where the inorder predecessor has a right son
                    {
                        cout << "inorder predecessor has a right son\n";
                        q->parent->left = q->right;
                        q->right->parent = q->parent;
                        q->right = NULL;
                        q->parent = NULL;
                        delete q;
                    }
                    else
                    {
                        q->parent->left = NULL;
                        q->parent = NULL;
                        delete q;
                    }
                }
                else
                {
                    p->value = q->value;

                    if(q->right)
                    {
                        r = q;
                        q->parent->right = r->right;
                        r->right->parent = q->parent;
                        r->right = NULL;
                        r->parent = NULL;
                        delete r;
                    }
                    else
                    {
                        q->parent->right = NULL;
                        q->parent = NULL;
                        delete q;
                    }
                }
            }
        }
    }
}


void AVL::doRotations(Node* &q,bool direction)
{
    if(direction)  //a node was inserted/deleted in the left subtree, so we proceed with right rotations
    {
        while(q)
        {
            if(height(q->left) - (height(q->right) )== 2 &&
                ( (( height(q->left->left) - height(q->left->right) ) == 1) ||
                (( height(q->left->left) - height(q->left->right) ) == 0 ) ))
            {
                // Right Rotation for : " << q->value.printInterval();
                rightRotation(q);
                break;
            }

            if(height(q->left) - (height(q->right) ) == -2 &&
                ( height(q->right->left) - height(q->right->right)) == 1)
            {
                // RightLeft Rotation for : " << q->value.printInterval();
                Node* t = q->right;
                rightLeftRotation(q);
                break;
            }

            q = q->parent;
        }
    }
    else //A node was inserted/deleted in the right subtree, so we proceed with left rotations
    {
        while(q)
        {
            if((height(q->left) - height(q->right) )== -2 &&
                (( height(q->right->left) - height(q->right->right) ) == -1 ||
                ( height(q->right->left) - height(q->right->right)) == 0 ) )
            {
                // Left rotation for " << q->value.printInterval();
                leftRotation(q);
                break;
            }

            if((height(q->left) - height(q->right) )== 2 &&
                ( height(q->left->left) - height(q->left->right)) == -1)
            {
                // LeftRight Rotation for : " << q->value.printInterval();
                leftRightRotation(q);
                break;
            }

            q = q->parent;
        }
    }
}

void AVL::insertNode(Interval val)
{
    Node* t;
    t = new Node(val);
    // INSERT NEW NODE : " Debug check:  val.printInterval()

    if(root)
    {
        Node* p = root;
        Node* q;

        int compVal;
        bool endLoop = false;
        while(p && !endLoop) //search for the right place to insert the node with the new value
        {
            q = p;
            // compare value (consider insertion too where no rotations are involved)
            compVal = val.compareTo(p->value);
            switch(compVal)
            {
                case -1:
                    p = p->left;
                    break;
                case 1:
                    p = p->right;
                    break;
                default:
                    endLoop = true;
                    break;
            }
        }

        compVal = val.compareTo(q->value);
        // For Debugging Reasons:
        //cout << "I got at the value : " << q->value.printInterval() << " , with compVale: "
        //     << compVal << endl ;
        switch(compVal)
        {
            case -1:
            {
                q->left = t; //insert node as the left leaf of q
                t->parent = q;
                cout << endl;
                doRotations(q,1);
                break;
            }
            case 1:
            {
                q->right = t; //insert node as the right leaf of q
                t->parent = q;
                doRotations(q,0);
                break;
            }
            case 3:
            {
                q->value.high = val.high;
                break;
            }
            case 4:
            {
                q->value.low = val.low;
                break;
            }
            case 5:
            {
                q->value.high = val.high;
                q->value.low = val.low;
                break;
            }

             // I ignore so far case 0 (equality) and 2 (total inclusion), so I just don't insert new intervals
            // in these cases
        }
    }
    else
        root = new Node(val);
}

void AVL::inorder(Node* someNode)
{
    if(someNode)
    {
        inorder(someNode->left);
        // Printing values in increasing order, one can also look at the
        // balance check of every node by: height(someNode->left) and height(someNode->right)
        cout << someNode->value.printInterval() << endl;

        inorder(someNode->right);
    }
}

void AVL::getSortedListFromAvl(std::vector<Interval>& sortedList)
{
    std::stack<Node *> s;
    Node *curr = this->getRoot();

    while (curr != NULL || s.empty() == false)
    {
        /* Reach the left most Node of the
           curr Node */
        while (curr !=  NULL)
        {
            s.push(curr);
            curr = curr->left;
        }

        /* Current must be NULL at this point */
        curr = s.top();
        s.pop();
        sortedList.push_back(curr->value);

        curr = curr->right;
    }
}
