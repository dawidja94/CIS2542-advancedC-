// FILE: sequenceList_exam.cpp
// Written by: Michael Main (main@colorado.edu) - Oct 31, 1997
// Non-interactive test program for the sequenceList class using a linked sequenceList
//
// DESCRIPTION:
// Each function of this program tests part of the sequenceList class, returning
// some number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...

#include <iostream>     // Provides cout.
#include <cstdlib>      // Provides size_t.
#include "sequenceList.h"  // Provides the sequenceList class with double items.
using namespace std;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 7;
const int POINTS[MANY_TESTS+1] = {
    35,  // Total points for all tests.
     3,  // Test 1 points
     2,  // Test 2 points
     8,  // Test 3 points
     4,  // Test 4 points
     5,  // Test 5 points
     3,  // Test 6 points
	 10  // Test 7 points
};
const char DESCRIPTION[MANY_TESTS+1][256] = {
    "tests for sequenceList Class with a linked sequenceList",
    "Testing insert, attach, and the constant member functions",
    "Testing situations where the cursor goes off the sequenceList",
    "Testing remove_current member function",
    "Testing the copy constructor",
    "Testing the assignment operator",
    "Testing insert/attach for somewhat larger sequenceLists",
	"Testing erase_one member function"
};


// **************************************************************************
// bool test_basic(const sequenceList& test, size_t s, bool has_cursor)
//   Postcondition: A return value of true indicates:
//     a. test.size() is s, and
//     b. test.is_item() is has_cursor.
//   Otherwise the return value is false.
//   In either case, a description of the test result is printed to cout.
// **************************************************************************
bool test_basic(const sequenceList& test, size_t s, bool has_cursor)
{
    bool answer;

    cout << "Testing that size() returns " << s << " ... ";
    cout.flush( );
    answer = (test.size( ) == s);
    cout << (answer ? "Passed." : "Failed.") << endl;

    if (answer)
    {
        cout << "Testing that is_item() returns ";
        cout << (has_cursor ? "true" : "false") << " ... ";
        cout.flush( );
        answer = (test.is_item( ) == has_cursor);
        cout << (answer ? "Passed." : "Failed.") << endl;
    }

    return answer;
}


// **************************************************************************
// bool test_items(sequenceList& test, size_t s, size_t i, double items[])
//   The function determines if the test sequenceList has the correct items
//   Precondition: The size of the items array is at least s.
//   Postcondition: A return value of true indicates that test.current()
//   is equal to items[i], and after test.advance() the result of
//   test.current() is items[i+1], and so on through items[s-1].
//   At this point, one more advance takes the cursor off the sequenceList.
//   If any of this fails, the return value is false.
//   NOTE: The test sequenceList has been changed by advancing its cursor.
// **************************************************************************
bool test_items(sequenceList& test, size_t s, size_t i, double items[])
{
    bool answer = true;

    cout << "The cursor should be at item [" << i << "]" << " of the sequenceList\n";
    cout << "(counting the first item as [0]). I will advance the cursor\n";
    cout << "to the end of the sequenceList, checking that each item is correct...";
    cout.flush( );
    while ((i < s) && test.is_item( ) && (test.current( ) == items[i]))
    {
        i++;
        test.advance( );
    }

    if ((i != s) && !test.is_item( ))
    {   // The test.is_item( ) function returns false too soon.
        cout << "\n    Cursor fell off the sequenceList too soon." << endl;
        answer = false;
    }
    else if (i != s)
    {   // The test.current( ) function returned a wrong value.
        cout << "\n    The item [" << i << "] should be " << items[i] << ",\n";
        cout << "    but it was " << test.current( ) << " instead.\n";
        answer = false;
    }
    else if (test.is_item( ))
    {   // The test.is_item( ) function returns true after moving off the sequenceList.
        cout << "\n    The cursor was moved off the sequenceList,";
        cout << " but is_item still returns true." << endl;
        answer = false;
    }

    cout << (answer ? "Passed." : "Failed.") << endl;
    return answer;
}


// **************************************************************************
// bool correct(sequenceList& test, size_t s, size_t cursor_spot, double items[])
//   This function determines if the sequenceList (test) is "correct" according to
//   these requirements:
//   a. it has exactly s items.
//   b. the items (starting at the front) are equal to
//      items[0] ... items[s-1]
//   c. if cursor_spot < s, then test's cursor must be at
//      the location given by cursor_spot.
//   d. if cursor_spot >= s, then test must not have a cursor.
// NOTE: The function also moves the cursor off the sequenceList.
// **************************************************************************
bool correct(sequenceList& test, size_t size, size_t cursor_spot, double items[])
{
    bool has_cursor = (cursor_spot < size);

    // Check the sequenceList's size and whether it has a cursor.
    if (!test_basic(test, size, has_cursor))
    {
        cout << "Basic test of size() or is_item() failed." << endl << endl;
        return false;
    }

    // If there is a cursor, check the items from cursor to end of the sequenceList.
    if (has_cursor && !test_items(test, size, cursor_spot, items))
    {
        cout << "Test of the sequenceList's items failed." << endl << endl;
        return false;
    }

    // Restart the cursor at the front of the sequenceList and test items again.
    cout << "I'll call start() and look at the items one more time..." << endl;
    test.start( );
    if (has_cursor && !test_items(test, size, 0, items))
    {
        cout << "Test of the sequenceList's items failed." << endl << endl;
        return false;
    }

    // If the code reaches here, then all tests have been passed.
    cout << "All tests passed for this sequenceList." << endl << endl;
    return true;
}


// **************************************************************************
// int test1( )
//   Performs some basic tests of insert, attach, and the constant member
//   functions. Returns POINTS[1] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test1( )
{
    sequenceList empty;                            // An empty sequenceList
    sequenceList test;                             // A sequenceList to add items to
    double items1[4] = { 5, 10, 20, 30 };  // These 4 items are put in a sequenceList
    double items2[4] = { 10, 15, 20, 30 }; // These are put in another sequenceList

    // Test that the empty sequenceList is really empty
    cout << "Starting with an empty sequenceList." << endl;
    if (!correct(empty, 0, 0, items1)) return 0;

    // Test the attach function to add something to an empty sequenceList
    cout << "I am now using attach to put 10 into an empty sequenceList." << endl;
    test.attach(10);
    if (!correct(test, 1, 0, items2)) return 0;

    // Test the insert function to add something to an empty sequenceList
    cout << "I am now using insert to put 10 into an empty sequenceList." << endl;
    test = empty;
    test.insert(10);
    if (!correct(test, 1, 0, items2)) return 0;

    // Test the insert function to add an item at the front of a sequenceList
    cout << "I am now using attach to put 10,20,30 in an empty sequenceList.\n";
    cout << "Then I move the cursor to the start and insert 5." << endl;
    test = empty;
    test.attach(10);
    test.attach(20);
    test.attach(30);
    test.start( );
    test.insert(5);
    if (!correct(test, 4, 0, items1)) return 0;

    // Test the insert function to add an item in the middle of a sequenceList
    cout << "I am now using attach to put 10,20,30 in an empty sequenceList.\n";
    cout << "Then I move the cursor to the start, advance once, ";
    cout << "and insert 15." << endl;
    test = empty;
    test.attach(10);
    test.attach(20);
    test.attach(30);
    test.start( );
    test.advance( );
    test.insert(15);
    if (!correct(test, 4, 1, items2)) return 0;

    // Test the attach function to add an item in the middle of a sequenceList
    cout << "I am now using attach to put 10,20,30 in an empty sequenceList.\n";
    cout << "Then I move the cursor to the start and attach 15 ";
    cout << "after the 10." << endl;
    test = empty;
    test.attach(10);
    test.attach(20);
    test.attach(30);
    test.start( );
    test.attach(15);
    if (!correct(test, 4, 1, items2)) return 0;

    // All tests have been passed
    cout << "All tests of this first function have been passed." << endl;
    return POINTS[1];
}


// **************************************************************************
// int test2( )
//   Performs a test to ensure that the cursor can correctly be run off the end
//   of the sequenceList. Also tests that attach/insert work correctly when there is
//   no cursor. Returns POINTS[2] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test2( )
{
    const size_t TESTSIZE = 30;
    sequenceList test;
    size_t i;

    // Put three items in the sequenceList
    cout << "Using attach to put 20 and 30 in the sequenceList, and then calling\n";
    cout << "advance, so that is_item should return false ... ";
    cout.flush( );
    test.attach(20);
    test.attach(30);
    test.advance( );
    if (test.is_item( ))
    {
        cout << "failed." << endl;
        return 0;
    }
    cout << "passed." << endl;

    // Insert 10 at the front and run the cursor off the end again
    cout << "Inserting 10, which should go at the sequenceList's front." << endl;
    cout << "Then calling advance three times to run cursor off the sequenceList ...";
    cout.flush( );
    test.insert(10);
    test.advance( ); // advance to the 20
    test.advance( ); // advance to the 30
    test.advance( ); // advance right off the sequenceList
    if (test.is_item( ))
    {
        cout << " failed." << endl;
        return false;
    }
    cout << " passed." << endl;

    // Attach more items until the sequenceList becomes full.
    // Note that the first attach should attach to the end of the sequenceList.
    cout << "Calling attach to put the numbers 40, 50, 60 ...";
    cout << TESTSIZE*10 << " at the sequenceList's end." << endl;
    for (i = 4; i <= TESTSIZE; i++)
        test.attach(i*10);

    // Test that the sequenceList is correctly filled.
    cout << "Now I will test that the sequenceList has 10, 20, 30, ...";
    cout << TESTSIZE*10 << "." << endl;
    test.start( );
    for (i = 1; i <= TESTSIZE; i++)
    {
        if ((!test.is_item( )) || test.current( ) != i*10)
        {
            cout << "    Test failed to find " << i*10 << endl;
            return 0;
        }
        test.advance( );
    }
    if (test.is_item( ))
    {
        cout << "    There are too many items on the sequenceList." << endl;
        return false;
    }

    // All tests passed
    cout << "All tests of this second function have been passed." << endl;
    return POINTS[2];
}


// **************************************************************************
// int test3( )
//   Performs basic tests for the remove_current function.
//   Returns POINTS[3] if the tests are passed.
//   Otherwise returns 0.
// **************************************************************************
int test3( )
{
    const size_t TESTSIZE = 30;

    sequenceList test;

    // Within this function, I create several different sequenceLists using the
    // items in these arrays:
    double items1[1] = { 30 };
    double items2[2] = { 10, 30 };
    double items3[3] = { 10, 20, 30 };

    size_t i;       // for-loop control variable

    // Build a sequenceList with three items 10, 20, 30, and remove the middle,
    // and last and then first.
    cout << "Using attach to build a sequenceList with 10,30." << endl;
    test.attach(10);
    test.attach(30);
    cout << "Insert a 20 before the 30, so entire sequenceList is 10,20,30." << endl;
    test.insert(20);
    if (!correct(test, 3, 1, items3)) return 0;
    cout << "Remove the 20, so entire sequenceList is now 10,30." << endl;
    test.start( );
    test.advance( );
    test.remove_current( );
    if (!correct(test, 2, 1, items2)) return 0;
    cout << "Remove the 30, so entire sequenceList is now just 10 with no cursor.";
    cout << endl;
    test.start( );
    test.advance( );
    test.remove_current( );
    if (!correct(test, 1, 1, items2)) return 0;
    cout << "Set the cursor to the start and remove the 10." << endl;
    test.start( );
    test.remove_current( );
    if (!correct(test, 0, 0, items2)) return 0;

    // Build a sequenceList with three items 10, 20, 30, and remove the middle,
    // and then first and then last.
    cout << "Using attach to build another sequenceList with 10,30." << endl;
    test.attach(10);
    test.attach(30);
    cout << "Insert a 20 before the 30, so entire sequenceList is 10,20,30." << endl;
    test.insert(20);
    if (!correct(test, 3, 1, items3)) return 0;
    cout << "Remove the 20, so entire sequenceList is now 10,30." << endl;
    test.start( );
    test.advance( );
    test.remove_current( );
    if (!correct(test, 2, 1, items2)) return 0;
    cout << "Set the cursor to the start and remove the 10," << endl;
    cout << "so the sequenceList should now contain just 30." << endl;
    test.start( );
    test.remove_current( );
    if (!correct(test, 1, 0, items1)) return 0;
    cout << "Remove the 30 from the sequenceList, resulting in an empty sequenceList." << endl;
    test.start( );
    test.remove_current( );
    if (!correct(test, 0, 0, items1)) return 0;

    // Build a sequenceList with three items 10, 20, 30, and remove the first.
    cout << "Build a new sequenceList by inserting 30, 10, 20 (so the sequenceList\n";
    cout << "is 20, then 10, then 30). Then remove the 20." << endl;
    test.insert(30);
    test.insert(10);
    test.insert(20);
    test.remove_current( );
    if (!correct(test, 2, 0, items2)) return 0;
    test.start( );
    test.remove_current( );
    test.remove_current( );

    // Just for fun, fill up the sequenceList, and empty it!
    cout << "Just for fun, I'll empty the sequenceList then fill it up, then\n";
    cout << "empty it again. During this process, I'll try to determine\n";
    cout << "whether any of the sequenceList's member functions access the\n";
    cout << "array outside of its legal indexes." << endl;
    for (i = 0; i < TESTSIZE; i++)
        test.insert(0);
    for (i = 0; i < TESTSIZE; i++)
        test.remove_current( );

    // All tests passed
    cout << "All tests of this third function have been passed." << endl;
    return POINTS[3];
}


// **************************************************************************
// int test4( )
//   Performs some tests of the copy constructor.
//   Returns POINTS[4] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test4( )
{
    const size_t TESTSIZE = 30;
    sequenceList original; // A sequenceList that we'll copy.
    double items[2*TESTSIZE];
    size_t i;

    // Set up the items array to conatin 1...2*TESTSIZE.
    for (i = 1; i <= 2*TESTSIZE; i++)
        items[i-1] = i;

    // Test copying of an empty sequenceList. After the copying, we change original.
    cout << "Copy constructor test: for an empty sequenceList." << endl;
    sequenceList copy1(original);
    original.attach(1); // Changes the original sequenceList, but not the copy.
    if (!correct(copy1, 0, 0, items)) return 0;

    // Test copying of a sequenceList with current item at the tail.
    cout << "Copy constructor test: for a sequenceList with cursor at tail." << endl;
    for (i=2; i <= 2*TESTSIZE; i++)
        original.attach(i);
    sequenceList copy2(original);
    original.remove_current( ); // Delete tail from original, but not the copy
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy2, 2*TESTSIZE, 2*TESTSIZE-1, items)
        )
        return 0;

    // Test copying of a sequenceList with cursor near the middle.
    cout << "Copy constructor test: with cursor near middle." << endl;
    original.insert(2);
    for (i = 1; i < TESTSIZE; i++)
        original.advance( );
    // Cursor is now at location [TESTSIZE] (counting [0] as the first spot).
    sequenceList copy3(original);
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy3, 2*TESTSIZE-1, TESTSIZE, items)
        )
        return 0;

    // Test copying of a sequenceList with cursor at the front.
    cout << "Copy constructor test: for a sequenceList with cursor at front." << endl;
    original.insert(2);
    original.start( );
    // Cursor is now at the front.
    sequenceList copy4(original);
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy4, 2*TESTSIZE-1, 0, items)
        )
        return 0;

    // Test copying of a sequenceList with no current item.
    cout << "Copy constructor test: for a sequenceList with no current item." << endl;
    original.insert(2);
    while (original.is_item( ))
        original.advance( );
    // There is now no current item.
    sequenceList copy5(original);
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy5, 2*TESTSIZE-1, 2*TESTSIZE, items)
        )
        return 0;

    // All tests passed
    cout << "All tests of this fourth function have been passed." << endl;
    return POINTS[4];
}


// **************************************************************************
// int test5( )
//   Performs some tests of the assignment operator.
//   Returns POINTS[5] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test5( )
{
    const size_t TESTSIZE = 30;
    sequenceList original; // A sequenceList that we'll copy.
    double items[2*TESTSIZE];
    size_t i;

    // Set up the items array to conatin 1...2*TESTSIZE.
    for (i = 1; i <= 2*TESTSIZE; i++)
        items[i-1] = i;

    // Test copying of an empty sequenceList. After the copying, we change original.
    cout << "Assignment operator test: for an empty sequenceList." << endl;
    sequenceList copy1;
    copy1 = original;
    original.attach(1); // Changes the original sequenceList, but not the copy.
    if (!correct(copy1, 0, 0, items)) return 0;

    // Test copying of a sequenceList with current item at the tail.
    cout << "Assignment operator test: cursor at tail." << endl;
    for (i=2; i <= 2*TESTSIZE; i++)
        original.attach(i);
    sequenceList copy2;
    copy2 = original;
    original.remove_current( ); // Delete tail from original, but not the copy
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy2, 2*TESTSIZE, 2*TESTSIZE-1, items)
        )
        return 0;

    // Test copying of a sequenceList with cursor near the middle.
    cout << "Assignment operator test: with cursor near middle." << endl;
    original.insert(2);
    for (i = 1; i < TESTSIZE; i++)
        original.advance( );
    // Cursor is now at location [TESTSIZE] (counting [0] as the first spot).
    sequenceList copy3;
    copy3 = original;
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy3, 2*TESTSIZE-1, TESTSIZE, items)
        )
        return 0;

    // Test copying of a sequenceList with cursor at the front.
    cout << "Assignment operator test: with cursor at front." << endl;
    original.insert(2);
    original.start( );
    // Cursor is now at the front.
    sequenceList copy4;
    copy4 = original;
    original.start( );
    original.advance( );
    original.remove_current( ); // Delete 2 from original, but not the copy.
    if (!correct
        (copy4, 2*TESTSIZE-1, 0, items)
        )
        return 0;

    // Test copying of a sequenceList with no current item.
    cout << "Assignment operator test: with no current item." << endl;
    original.insert(2);
    while (original.is_item( ))
        original.advance( );
    // There is now no current item.
    sequenceList copy5;
    copy5 = original;
    original.start( );
    original.advance( );
    original.remove_current( ); // Deletes 2 from the original, but not copy.
    if (!correct
        (copy5, 2*TESTSIZE-1, 2*TESTSIZE, items)
        )
        return 0;

    cout << "Checking correctness of a self-assignment x = x;" << endl;
    original.insert(2);
    original = original;
    if (!correct
        (original, 2*TESTSIZE-1, 1, items)
        )
        return 0;

    // All tests passed
    cout << "All tests of this fifth function have been passed." << endl;
    return POINTS[5];
}


// **************************************************************************
// int test6( )
//   Performs some basic tests of insert and attach for the case where the
//   current capacity has been reached.
//   Returns POINTS[6] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test6( )
{
    const size_t TESTSIZE = 30;
    sequenceList testa, testi;
    double items[2*TESTSIZE];
    size_t i;

    // Set up the items array to conatin 1...2*TESTSIZE.
    for (i = 1; i <= 2*TESTSIZE; i++)
        items[i-1] = i;

    cout << "Testing to see that attach works correctly when the\n";
    cout << "current capacity is exceeded." << endl;
    for (i = 1; i <= 2*TESTSIZE; i++)
        testa.attach(i);
    if (!correct
        (testa, 2*TESTSIZE, 2*TESTSIZE-1, items)
        )
        return 0;

    cout << "Testing to see that insert works correctly when the\n";
    cout << "current capacity is exceeded." << endl;
    for (i = 2*TESTSIZE; i >= 1; i--)
        testi.insert(i);
    if (!correct
        (testi, 2*TESTSIZE, 0, items)
        )
        return 0;

    // All tests passed
    cout << "All tests of this sixth function have been passed." << endl;
    return POINTS[6];
}


// **************************************************************************
// int test7( )
//   Performs a test to ensure that the erase_one(...) correctly removes
//   an item of the sequenceDynamic. Returns POINTS[8] if the tests are passed. 
//   Otherwise returns 0.
// **************************************************************************
int test7()
{
	sequenceList testDup, testUnique;
	size_t i, j;
	// array of duplicate items
	int items3[3] = { 10, 10, 10 };
	size_t arrSize3 = sizeof(items3) / sizeof(int);
	// array of unique items
	int items5[5] = { 10, 20, 30, 40, 50 };
	size_t arrSize5 = sizeof(items5) / sizeof(int);

	// put items in the sequenceDynamic of duplicates
	cout << "Attaching ";
	for (i = 0; i < arrSize3; i++) {
		cout << items3[i] << " ";
		testDup.attach(items3[i]);
	}
	cout << "to sequenceList of duplicate items." << endl;
	// try to erase item not found
	cout << "Attempting to erase item not in sequenceList...";
	if (testDup.erase_one(100)) {
		if (testDup.size() != arrSize3) {
			cout << "failed." << endl;
			return 0;
		}
	}
	cout << "passed." << endl;
	// remove items from sequenceDynamic of duplicates
	cout << "Erasing duplicate items...";
	for (i = 0; i < arrSize3; i++) {
		if (testDup.erase_one(items3[i])) {
			// position cursor at beginning
			testDup.start();
			// check size after removed
			if (testDup.size() + 1 != arrSize3 - i) {
				cout << "failed." << endl;
				return 0;
			}
			cout << "\n\tverifying remaining items in sequenceList...";
			// check that all remaining items are in sequence
			for (j = i + 1; j < arrSize3; j++) {
				if (testDup.current() != items3[j]) {
					cout << "failed." << endl;
					return 0;
				}
				else
					testDup.advance();
			}
		}
	}
	cout << "passed." << endl;

	// put items in the sequenceDynamic of unique items
	cout << "Attaching ";
	for (i = 0; i < arrSize5; i++) {
		cout << items5[i] << " ";
		testUnique.attach(items5[i]);
	}
	cout << "to sequenceList of unique items." << endl;
	// remove all items from non-duplicate array
	cout << "Erasing unique items...";
	for (i = 0; i < arrSize5; i++) {
		if (testUnique.erase_one(items5[i])) {
			// position cursor at beginning
			testUnique.start();
			// check size after removed
			if (testUnique.size() + 1 != arrSize5 - i) {
				cout << "failed." << endl;
				return 0;
			}
			cout << "\n\tverifying remaining items in sequenceList...";
			// check that all remaining items are in sequence
			for (j = i + 1; j < arrSize5; j++) {
				if (testUnique.current() != items5[j]) {
					cout << "failed." << endl;
					return 0;
				}
				else
					testUnique.advance();
			}
		}
		else {
			cout << "item not found...failed." << endl;
			return 0;
		}
	}
	cout << "passed." << endl;

	// All tests passed
	cout << "All tests of this seventh function have been passed." << endl;
	return POINTS[7];
}

int run_a_test(int number, const char message[], int test_function( ), int max)
{
    int result;

    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;

    return result;
}


// **************************************************************************
// int main( )
//   The main program calls all tests and prints the sum of all points
//   earned from the tests.
// **************************************************************************
int main( )
{
	int stuPoints[MANY_TESTS + 1], sum = 0;

    cout << "Running " << DESCRIPTION[0] << endl;
	// run tests and identify points awarded
	stuPoints[1] = run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
	stuPoints[2] = run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
	stuPoints[3] = run_a_test(3, DESCRIPTION[3], test3, POINTS[3]); 
	stuPoints[4] = run_a_test(4, DESCRIPTION[4], test4, POINTS[4]); 
	stuPoints[5] = run_a_test(5, DESCRIPTION[5], test5, POINTS[5]); 
	stuPoints[6] = run_a_test(6, DESCRIPTION[6], test6, POINTS[6]); 
	stuPoints[7] = run_a_test(7, DESCRIPTION[7], test7, POINTS[7]);

	// accumulate points
	for (int i = 1; i <= MANY_TESTS; i++)
		sum += stuPoints[i];

	// output testing results
	cout << "==========>TEST RESULTS<==========" << endl;
	cout << "If you submit this sequenceList class now, you will have\n";
	cout << sum << " points out of the " << POINTS[0];
	cout << " points from this test program.\n";

	cout << "==========>POINT SUMMARY<==========" << endl;
	for (int i = 1; i <= MANY_TESTS; i++)
		cout << DESCRIPTION[i] << "\n\tPOINTS = " << stuPoints[i] << " out of " << POINTS[i] << endl;
    return EXIT_SUCCESS;

}
