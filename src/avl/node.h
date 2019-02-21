#ifndef NODE_H
#define NODE_H

#include <iostream>

/*! @brief Interval class which holds the information about a closed interval. It
           checks for the following cases:
           1. Full inclusion: the interval to be added is already included in other interval, in this case no new
              node is added.
           2. Partial inclusion: where the high of the other object becomes high of the current one
                    Ex: compare [14,23] (to insert) to [2,19] (existing) which must be merged to [2,23]
           3. Partial inclusion where the low of the other object becomes low of the current one
                    Ex: compare [8,18] (existing) to [6,15] (to insert) to  which must be merged to [6,18]
           4. The new interval can include the current interval.
                    Ex: [1,24] (to insert) includes [2, 23], so [2, 23] is replaced by [1,24]
*/
struct Interval
{
    int low;
    int high;

    Interval(int l, int h)
    {
        low = l;
        high = h;
    }

    std::string printInterval()
    {
        std::string printIntv = "[" + std::to_string(low) + "," + std::to_string(high) + "]";
        return  printIntv;
    }

    int compareTo(Interval ob)
    {
        // equal
        if(low == ob.low && high == ob.high)
        {
            return 0;
        }

        // smaller
        if(high < ob.low)
        {
            return -1;
        }

        // bigger
        if(low > ob.high)
        {
            return 1;
        }

        // check full inclusion
        if(high <= ob.high && low >= ob.low)
        {
            return 2;
        }

        // check partial inclusion where the high of the other object becomes high of the current one
        // Ex: compare [14,23] (to insert) to [2,19] (existing) which must be merged to [2,23]
        if(ob.high < high && ob.low < low)
        {
            return 3;
        }

        // check partial inclusion where the low of the other object becomes low of the current one
        // Ex: compare [8,18] to [6,15] to  which must be merged to [6,18]
        if(ob.low > low && ob.high > high)
        {
            return 4;
        }

        // check if the new interval can include the current interval
        if(low < ob.low && high > ob.high)
        {
            return 5;
        }

        std::cout << "No match for : " << low << ", " << high << std::endl;
        // return value for no match
        return -2;
    }

};

/*! @brief Node class used to hold the information of  an AVLTree. This information is the
 *         typical information used for BST trees, to which height, left and right
 *         height are added.
*/
class Node
{
    public:
        Node(Interval val) : value(val)
        {
            left = right = parent = NULL;
            height = 0;
            lHeight = 0;
            rHeight = 0;
        }

        Node* left;
        Node* right;
        Node* parent;
        int height;
        int lHeight;
        int rHeight;
        Interval value;
};

#endif // NODE_H
