1.  This is an implementation of an AVL Tree having as nodes values closed integer intervals of the form
    [4, 16], where 4 is the left-bounded value and 16 is right-bounded value. 
    For simplicity, I call these values low and high. 

    An AVL tree is a self balancing binary search tree (BST) in which the maximum difference in height of any node's
    left and right subtrees is 1, this is also called balance factor which can be defined like this:

			balance factor = height(right) - height(left)

	Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases, 
	where n is the number of nodes in the tree prior to the operation.

	In this particular implementation, new values are added to the tree like in a BST or just merged to other
	nodes in the following cases:

	a. Full inclusion: the interval to be added is already included in other interval, in this case no new 
	   node is added.
	b. Partial inclusion: where the high of the other object becomes high of the current one
			Ex: compare [14,23] (to insert) to [2,19] (existing) which must be merged to [2,23]
	c. Partial inclusion where the low of the other object becomes low of the current one
			Ex: compare [8,18] (existing) to [6,15] (to insert) to  which must be merged to [6,18]
	d. The new interval can include the current interval. 
			Ex: [1,24] (to insert) includes [2, 23], so [2, 23] is replaced by [1,24]
 
2.  You may find also find a complete Doxygen documentation of the AVL implementation in MergingIntervals/docs/html/index.html
 
3.  Testing of the merging intervals with AVL is done with the Catch Library and are provided in
		MergingIntervals/test/test_avl_merging_intervals.cpp which can of course be extended with other
		tests.
        
3.  Build Steps (tested already in Mac Os, Ubuntu and Windows 7 with Visual Studio Express Edition 2015)

	1. For both Unix OS-es and Windows run the main CMakeLists.txt found in the MergingIntervals folder:
	
			cmake CMakeLists.txt
			
	2. 
		
		a. For Unix: Run: make 
	
			This will create:
			  a. The MergingIntervals/src/MergingIntervalsProject main application binary file 
			  b. The MergingIntervals/test/test_intervals_with_avl test binary file
			  
		b. For Windows: Because of Catch Library, the project Visual Studio 2015 or higher version.
		   CMake will create MergingIntervals.sln which one can open in Visual Studio.
