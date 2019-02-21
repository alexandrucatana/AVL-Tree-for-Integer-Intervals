#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "avl.h"
#include <vector>


TEST_CASE( "Test Merging Intervals with AVL Tree", "[A lot of merging]" )
{
    AVL avl;
    Interval intv_one(25, 30);
    Interval intv_two(2, 19);
    // The following must expand (2, 19) on the high value to (2, 23)
    Interval intv_three(14, 23);
    // The following will be included in the newly formed interval (2, 23)
    Interval intv_four(4, 8);
    // The following will include (2, 23) and extend it on both low and high to form (1, 24)
    Interval intv_five(1, 24);

    avl.insertNode(intv_one);
    avl.insertNode(intv_two);
    avl.insertNode(intv_three);
    avl.insertNode(intv_four);
    avl.insertNode(intv_five);

    std::vector<Interval> sortedList;
    avl.getSortedListFromAvl(sortedList);

    REQUIRE(sortedList.at(0).low == 1 );
    REQUIRE(sortedList.at(0).high == 24);
    REQUIRE(sortedList.at(1).low == 25);
    REQUIRE(sortedList.at(1).high == 30);

    REQUIRE(sortedList.at(0).compareTo(intv_five) == 0);
    REQUIRE(sortedList.at(1).compareTo(intv_one) == 0);
}

TEST_CASE( "Test Non Merging Intervals with AVL Tree", "[No merging]" )
{
    AVL avl;
    Interval intv_one(50, 60);
    Interval intv_two(42, 44);
    Interval intv_three(38, 41);
    Interval intv_four(100, 120);
    Interval intv_five(70, 80);

    avl.insertNode(intv_one);
    avl.insertNode(intv_two);
    avl.insertNode(intv_three);
    avl.insertNode(intv_four);
    avl.insertNode(intv_five);

    std::vector<Interval> sortedList;
    avl.getSortedListFromAvl(sortedList);

    REQUIRE(sortedList.at(0).compareTo(intv_three) == 0);
    REQUIRE(sortedList.at(1).compareTo(intv_two) == 0);
    REQUIRE(sortedList.at(2).compareTo(intv_one) == 0);
    REQUIRE(sortedList.at(3).compareTo(intv_five) == 0);
    REQUIRE(sortedList.at(4).compareTo(intv_four) == 0);
}

TEST_CASE( "Test changing value of the initial inserted intervals in AVL Tree", "[Changing initial value of Intervals]" )
{
    AVL avl;
    Interval intv_one(60, 80);
    // The following must expand (60, 80) on the high value to (60, 90)
    Interval intv_two(70, 90);
    Interval intv_three(30, 50);
    // The following must expand (30, 50)  on the high value to (30, 55)
    Interval intv_four(40, 55);
    Interval intv_five(100, 120);
    // The following must expand (100, 120) on the low value to (95, 120)
    Interval intv_six(95, 110);
    // The following must lead to a total inclusion of (60, 90) to (59, 92)
    Interval intv_seven(59, 92);

    avl.insertNode(intv_one);
    avl.insertNode(intv_two);
    avl.insertNode(intv_three);
    avl.insertNode(intv_four);
    avl.insertNode(intv_five);
    avl.insertNode(intv_six);
    avl.insertNode(intv_seven);

    Interval test_intv_lowest(30, 55);
    Interval test_intv_root(59, 92);
    Interval test_intv_highest(95, 120);

    std::vector<Interval> sortedList;
    avl.getSortedListFromAvl(sortedList);

    REQUIRE(sortedList.at(0).compareTo(test_intv_lowest) == 0);
    // Check if the middle value is the same as the root value
    REQUIRE(avl.getRoot()->value.compareTo(sortedList.at(1)) == 0);
    // Check also if the second value in the array is the same to the test root value
    REQUIRE(sortedList.at(1).compareTo(test_intv_root) == 0);
    REQUIRE(sortedList.at(2).compareTo(test_intv_highest) == 0);
}

