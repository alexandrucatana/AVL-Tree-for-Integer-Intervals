#include <iostream>
#include "avl.h"

using namespace std;

int main()
{
    AVL avl;
    Interval intv_one(25, 30);
    Interval intv_two(2, 19);
    Interval intv_three(14, 23);
    Interval intv_four(4, 8);
    Interval intv_five(1, 24);

    avl.insertNode(intv_one);
    avl.insertNode(intv_two);
    avl.insertNode(intv_three);
    avl.insertNode(intv_four);
    avl.insertNode(intv_five);

    cout << "INORDER : \n";
    avl.inorder(avl.getRoot());

    cout << endl;
}
