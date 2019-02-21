#ifndef AVL_H
#define AVL_H

#include "node.h"


/*! @brief AVL class used for building an AVL (Adelson-Velsky and Landis) Tree.
 *         The node values in this particular implementation are closed integer
 *         intervals of the form [4, 16], where 4 is the left-bounded value and
 *         16 is right-bounded value. For simplicity, I call these values low and high.
 *
 *         An AVL Tree is a self balancing Binary Search Tree (BST) in which the maximum
 *         difference in height of any node's left and right subtrees is 1, this is also
 *         called balance factor which can be defined like this:

                    balance factor = height(right) - height(left)

           Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases,
           where n is the number of nodes in the tree prior to the operation.
           Insertions and Deletions may require rebalancing by rotations.

           The following class implements four types
 *         of insertions: left, right, left-right and right-left insertions.
 *
 *         In this particular implementation, new values are added to the tree like in a BST or just merged to other
           nodes in the following cases:

           1. Full inclusion: the interval to be added is already included in other interval, in this case no new
              node is added.
           2. Partial inclusion: where the high of the other object becomes high of the current one
                    Ex: compare [14,23] (to insert) to [2,19] (existing) which must be merged to [2,23]
           3. Partial inclusion where the low of the other object becomes low of the current one
                    Ex: compare [8,18] (existing) to [6,15] (to insert) to  which must be merged to [6,18]
           4. The new interval can include the current interval.
                    Ex: [1,24] (to insert) includes [2, 23], so [2, 23] is replaced by [1,24]

    @author Alexandru Catana
    @date May 2011, Updated: February 2019
    */
class AVL
{
    private:
        Node* root;

        /*! @brief Calculates the balance factor of each node
         * @param Node for which the balance factor is calculated
         * @return integer value of the balance factor
         */
        int height(Node*);
        /*! @brief Based on the ballance factor of each node, the method decides
         *         which rotation method should be called if this is the case.
         * @param Node which acts like a pivot for the rotations
         */
        void doRotations(Node* &,bool);
        /*! @brief  A Node N has balance factor +2 and its right node N_Right has a ballance factor
                   +1  which means its right subree is too long. To balance this tree one replaces
                   N with its N_Right and consequently:
                        1. N becomes the left child of N_Right
                        2. N_Right's left subtree becomes the right subtree of N

           @param Node which acts like a pivot for the rotations
           @param Flag used to for either left or right subtree
         */
        void leftRotation(Node* &);
        /*! @brief A Node N has balance factor -2 and its left node N_Left has a ballance factor
                  -1  which means its left subree is too long. To balance this tree one replaces
                   N with its N_Left and consequently:
                        1. N becomes the right child of N_Left
                        2. N_Left's right subtree becomes the left subtree of N

           @param Node which acts like a pivot for the rotations
         */
        void rightRotation(Node* &);
        /*! @brief A Node N has balance factor -2 and its left node N_Left has a ballance factor
                  +1  which means its left subree is too long. To balance this tree one does
                  first a left rotation on N_Left and then a right rotation on N, thus:
                        1. Replace N_Left with its right child, called grandchild.
                        2. Replace N with the grandchild

           @param Node which acts like a pivot for the rotations
         */
        void leftRightRotation(Node* &);
        /*! @brief A Node N has balance factor +2 and its right node N_Right has a ballance factor
                  -1  which means its right subree is too long. To balance this tree one does
                  first a right rotation on N_Right and then a left rotation on N, thus:
                        1.Replace N_Right with its left child, called grandchild.
                        2. Replace N with the grandchild

           @param Node which acts like a pivot for the rotations
         */
        void rightLeftRotation(Node* &);

    public:
        /*! @brief Default constructor. Initializes the AVL root
         */
        AVL(){root = NULL;}
        /*! @brief Destructor. Deletes root
         */
        ~AVL(){delete root;}

        /*! @brief Method which inserts a new closed interval in the AVL Tree.
         *  The method checks the balance factor of the tree at every insertion
         *  calling the corresponding rotation method in case the tree is not
         *  ballanced anymore.
            @param param1 value to insert
        */
        void insertNode(Interval val);
        /*! @brief Traverses Tree in Inorder:
         * 1. Check if the current node is empty or null.
         * 2. Traverse the left subtree by recursively calling the in-order function.
         * 3. Display the data part of the root (or current node).
         * 4. Traverse the right subtree by recursively calling the in-order function.
         *
         * @param param1 Node from which the search can start from
         */
        void inorder(Node*);
        /*! @brief getRoot
         * @return the root of the AVL tree.
         */
        Node* getRoot(){return root;}

        /*! @brief The search tree is broadened as much as possible on each depth before
         *         going to the next depth.
         */
        void breadthFirst(Node*);
        /*!
         * @brief Method which deletes an interval from the tree, making sure
         *        that the AVL is rebalanced.
         * @param Interval to delete
         */
        void deleteNode(Interval val);
        /*!
         * @brief Finds Node by value, searching in an AVL Tree is the same as that in Binary Search Tree:
                  the key in each node must be greater than or equal to any key stored in the left sub-tree,
                  and less than or equal to any key stored in the right sub-tree.

         * @param the value to search for.
         * @return Node: the found node.
         */
        Node* findNode(Interval val);

        /*!
         * @brief Provides a sorted  list from the AVL tree by traversing the
         *         the tree in inorder.

         * @param Output: the resulted sorted list
         */
        void getSortedListFromAvl(std::vector<Interval>& sortedList);
};


#endif // AVL_H
