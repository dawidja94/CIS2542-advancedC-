// FILE: sequenceFixed_exam.cpp
// Written by: Michael Main (main@colorado.edu) - Oct 22, 1997
// Modified by: CREngland (england@cod.edu) 9/11/2018
//Modified by: Dawid Jasionowski 09/12/2018
// Non-interactive test program for the sequenceFixed class from Section 3.2 of
// "Data Structures and Other Objects".
//
// Each function of this program tests part of the sequenceFixed class, returning
// some number of points to indicate how much of the test was passed.
// A description and result of each test is printed to cout.
//
// Maximum number of points awarded by this program is determined by the
// constants POINTS[1], POINTS[2]...


#include <iostream>   // Provides cout.
#include <cstdlib>    // Provides size_t.
#include "sequenceFixed.h"    // Provides the sequenceFixed class with double items.
using namespace std;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 4;
const int POINTS[MANY_TESTS + 1] = {
	30, // Total points for all tests.
	7,  // Test 1 points
	6,  // Test 2 points
	7,  // Test 3 points
	10  // Test 4 points
};
const char DESCRIPTION[MANY_TESTS + 1][256] = {
	"tests for Chapter 3 sequenceFixed Class",
	"Testing insert, attach, and the constant member functions",
	"Testing situations where the cursor goes off the sequenceFixed when using attach and remove_current member functions",
	"Testing remove_current member function",
	"Testing erase_one member function"
};


// **************************************************************************
// bool test_basic(const sequenceFixed& test, size_t s, bool has_cursor)
//   Postcondition: A return value of true indicates:
//     a. test.size() is s, and
//     b. test.is_item() is has_cursor.
//   Otherwise the return value is false.
//   In either case, a description of the test result is printed to cout.
// **************************************************************************
bool test_basic(const sequenceFixed& test, size_t s, bool has_cursor)
{
	bool answer;

	cout << "Testing that size() returns " << s << " ... ";
	cout.flush();
	answer = (test.size() == s);
	cout << (answer ? "Passed." : "Failed.") << endl;

	if (answer)
	{
		cout << "Testing that is_item() returns ";
		cout << (has_cursor ? "true" : "false") << " ... ";
		cout.flush();
		answer = (test.is_item() == has_cursor);
		cout << (answer ? "Passed." : "Failed.") << endl;
	}

	return answer;
}


// **************************************************************************
// bool test_items(sequenceFixed& test, size_t s, size_t i, double items[])
//   The function determines if the test sequenceFixed has the correct items
//   Precondition: The size of the items array is at least s.
//   Postcondition: A return value of true indicates that test.current()
//   is equal to items[i], and after test.advance() the result of
//   test.current() is items[i+1], and so on through items[s-1].
//   At this point, one more advance takes the cursor off the sequenceFixed.
//   If any of this fails, the return value is false.
//   NOTE: The test sequenceFixed has been changed by advancing its cursor.
// **************************************************************************
bool test_items(sequenceFixed& test, size_t s, size_t i, double items[])
{
	bool answer = true;

	cout << "The cursor should be at item [" << i << "]" << " of the sequenceFixed\n";
	cout << "(counting the first item as [0]). I will advance the cursor\n";
	cout << "to the end of the sequenceFixed, checking that each item is correct...";
	cout.flush();
	while ((i < s) && test.is_item() && (test.current() == items[i]))
	{
		i++;
		test.advance();
	}

	if ((i != s) && !test.is_item())
	{   // The test.is_item( ) function returns false too soon.
		cout << "\n    Cursor fell off the sequenceFixed too soon." << endl;
		answer = false;
	}
	else if (i != s)
	{   // The test.current( ) function returned a wrong value.
		cout << "\n    The item [" << i << "] should be " << items[i] << ",\n";
		cout << "    but it was " << test.current() << " instead.\n";
		answer = false;
	}
	else if (test.is_item())
	{   // The test.is_item( ) function returns true after moving off the sequenceFixed.
		cout << "\n    The cursor was moved off the sequenceFixed,";
		cout << " but is_item still returns true." << endl;
		answer = false;
	}

	cout << (answer ? "Passed." : "Failed.") << endl;
	return answer;
}


// **************************************************************************
// bool correct(sequenceFixed test, size_t s, size_t cursor_spot, double items[])
//   This function determines if the sequenceFixed (test) is "correct" according to
//   these requirements:
//   a. it has exactly s items.
//   b. the items (starting at the front) are equal to
//      double[0] ... double[size-1]
//   c. if cursor_spot < size, then test's cursor must be at
//      the location given by cursor_spot.
//   d. if cursor_spot >= size, then test must not have a cursor.
// NOTE: The function also moves the cursor off the sequenceFixed.
// **************************************************************************
bool correct(sequenceFixed& test, size_t size, size_t cursor_spot, double items[])
{
	bool has_cursor = (cursor_spot < size);

	// Check the sequenceFixed's size and whether it has a cursor.
	if (!test_basic(test, size, has_cursor))
	{
		cout << "Basic test of size() or is_item() failed." << endl << endl;
		return false;
	}

	// If there is a cursor, check the items from cursor to end of the sequenceFixed.
	if (has_cursor && !test_items(test, size, cursor_spot, items))
	{
		cout << "Test of the sequenceFixed's items failed." << endl << endl;
		return false;
	}

	// Restart the cursor at the front of the sequenceFixed and test items again.
	cout << "I'll call start() and look at the items one more time..." << endl;
	test.start();
	if (has_cursor && !test_items(test, size, 0, items))
	{
		cout << "Test of the sequenceFixed's items failed." << endl << endl;
		return false;
	}

	// If the code reaches here, then all tests have been passed.
	cout << "All tests passed for this sequenceFixed." << endl << endl;
	return true;
}


// **************************************************************************
// int test1( )
//   Performs some basic tests of insert, attach, and the constant member
//   functions. Returns POINTS[1] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test1()
{
	sequenceFixed empty;                            // An empty sequenceFixed
	sequenceFixed test;                             // A sequenceFixed to add items to
	double items1[4] = { 5, 10, 20, 30 };  // These 4 items are put in a sequenceFixed
	double items2[4] = { 10, 15, 20, 30 }; // These are put in another sequenceFixed

	// Test that the empty sequenceFixed is really empty
	cout << "Starting with an empty sequenceFixed." << endl;
	if (!correct(empty, 0, 0, items1)) return 0;

	// Test the attach function to add something to an empty sequenceFixed
	cout << "I am now using attach to put 10 into an empty sequenceFixed." << endl;
	test.attach(10);
	if (!correct(test, 1, 0, items2)) return 0;

	// Test the insert function to add something to an empty sequenceFixed
	cout << "I am now using insert to put 10 into an empty sequenceFixed." << endl;
	test = empty;
	test.insert(10);
	if (!correct(test, 1, 0, items2)) return 0;

	// Test the insert function to add an item at the front of a sequenceFixed
	cout << "I am now using attach to put 10,20,30 in an empty sequenceFixed.\n";
	cout << "Then I move the cursor to the start and insert 5." << endl;
	test = empty;
	test.attach(10);
	test.attach(20);
	test.attach(30);
	test.start();
	test.insert(5);
	if (!correct(test, 4, 0, items1)) return 0;

	// Test the insert function to add an item in the middle of a sequenceFixed
	cout << "I am now using attach to put 10,20,30 in an empty sequenceFixed.\n";
	cout << "Then I move the cursor to the start, advance once, ";
	cout << "and insert 15." << endl;
	test = empty;
	test.attach(10);
	test.attach(20);
	test.attach(30);
	test.start();
	test.advance();
	test.insert(15);
	if (!correct(test, 4, 1, items2)) return 0;

	// Test the attach function to add an item in the middle of a sequenceFixed
	cout << "I am now using attach to put 10,20,30 in an empty sequenceFixed.\n";
	cout << "Then I move the cursor to the start and attach 15 ";
	cout << "after the 10." << endl;
	test = empty;
	test.attach(10);
	test.attach(20);
	test.attach(30);
	test.start();
	test.attach(15);
	if (!correct(test, 4, 1, items2)) return 0;

	// All tests have been passed
	cout << "All tests of this first function have been passed." << endl;
	return POINTS[1];
}


// **************************************************************************
// int test2( )
//   Performs a test to ensure that the cursor can correctly be run off the end
//   of the sequenceFixed. Also tests that attach/insert work correctly when there is
//   no cursor. Returns POINTS[2] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test2()
{
	sequenceFixed test;
	size_t i;

	// Put three items in the sequenceFixed
	cout << "Using attach to put 20 and 30 in the sequenceFixed, and then calling\n";
	cout << "advance, so that is_item should return false ... ";
	cout.flush();
	test.attach(20);
	test.attach(30);
	test.advance();
	if (test.is_item())
	{
		cout << "failed." << endl;
		return 0;
	}
	cout << "passed." << endl;

	// Insert 10 at the front and run the cursor off the end again
	cout << "Inserting 10, which should go at the sequenceFixed's front." << endl;
	cout << "Then calling advance three times to run cursor off the sequenceFixed ...";
	cout.flush();
	test.insert(10);
	test.advance(); // advance to the 20
	test.advance(); // advance to the 30
	test.advance(); // advance right off the sequenceFixed
	if (test.is_item())
	{
		cout << " failed." << endl;
		return false;
	}
	cout << " passed." << endl;

	// Attach more items until the sequenceFixed becomes full.
	// Note that the first attach should attach to the end of the sequenceFixed.
	cout << "Calling attach to put the numbers 40, 50, 60 ...";
	cout << test.CAPACITY * 10 << " at the sequenceFixed's end." << endl;
	for (i = 4; i <= test.CAPACITY; i++)
		test.attach(i * 10);

	// Test that the sequenceFixed is correctly filled.
	cout << "Now I will test that the sequenceFixed has 10, 20, 30, ...";
	cout << test.CAPACITY * 10 << "." << endl;
	test.start();
	for (i = 1; i <= test.CAPACITY; i++)
	{
		if ((!test.is_item()) || test.current() != i * 10)
		{
			cout << "    Test failed to find " << i * 10 << endl;
			return 0;
		}
		test.advance();
	}
	if (test.is_item())
	{
		cout << "    There are too many items on the sequenceFixed." << endl;
		return false;
	}

	// All tests passed
	cout << "All tests of this second function have been passed." << endl;
	return POINTS[2];
}


// **************************************************************************
// int test3( )
//   Performs basic tests for the remove_current function.
//   Returns POINTS[3] if the tests are passed. Returns POINTS[3] / 4 if almost
//   all the tests are passed. Otherwise returns 0.
// **************************************************************************
int test3()
{
	// In the next declarations, I am declaring a sequenceFixed called test.
	// Both before and after the sequenceFixed, I declare a small array of characters,
	// and I put the character 'x' into each spot of these arrays.
	// Later, if I notice that one of the x's has been changed, or if
	// I notice an 'x' inside of the sequenceFixed, then the most
	// likely reason was that one of the sequenceFixed's member functions accessed
	// the sequenceFixed's array outside of its legal indexes.
	char prefix[4] = { 'x', 'x', 'x', 'x' };
	sequenceFixed test;
	char suffix[4] = { 'x', 'x', 'x', 'x' };

	// Within this function, I create several different sequenceFixeds using the
	// items in these arrays:
	double items1[1] = { 30 };
	double items2[2] = { 10, 30 };
	double items3[3] = { 10, 20, 30 };

	size_t i;       // for-loop control variable
	char *char_ptr; // Variable to loop at each character in a sequenceFixed's memory

	// Build a sequenceFixed with three items 10, 20, 30, and remove the middle,
	// and last and then first.
	cout << "Using attach to build a sequenceFixed with 10,30." << endl;
	test.attach(10);
	test.attach(30);
	cout << "Insert a 20 before the 30, so entire sequenceFixed is 10,20,30." << endl;
	test.insert(20);
	if (!correct(test, 3, 1, items3)) return 0;
	cout << "Remove the 20, so entire sequenceFixed is now 10,30." << endl;
	test.start();
	test.advance();
	test.remove_current();
	if (!correct(test, 2, 1, items2)) return 0;
	cout << "Remove the 30, so entire sequenceFixed is now just 10 with no cursor.";
	cout << endl;
	test.start();
	test.advance();
	test.remove_current();
	if (!correct(test, 1, 1, items2)) return 0;
	cout << "Set the cursor to the start and remove the 10." << endl;
	test.start();
	test.remove_current();
	if (!correct(test, 0, 0, items2)) return 0;

	// Build a sequenceFixed with three items 10, 20, 30, and remove the middle,
	// and then first and then last.
	cout << "Using attach to build another sequenceFixed with 10,30." << endl;
	test.attach(10);
	test.attach(30);
	cout << "Insert a 20 before the 30, so entire sequenceFixed is 10,20,30." << endl;
	test.insert(20);
	if (!correct(test, 3, 1, items3)) return 0;
	cout << "Remove the 20, so entire sequenceFixed is now 10,30." << endl;
	test.start();
	test.advance();
	test.remove_current();
	if (!correct(test, 2, 1, items2)) return 0;
	cout << "Set the cursor to the start and remove the 10," << endl;
	cout << "so the sequenceFixed should now contain just 30." << endl;
	test.start();
	test.remove_current();
	if (!correct(test, 1, 0, items1)) return 0;
	cout << "Remove the 30 from the sequenceFixed, resulting in an empty sequenceFixed." << endl;
	test.start();
	test.remove_current();
	if (!correct(test, 0, 0, items1)) return 0;

	// Build a sequenceFixed with three items 10, 20, 30, and remove the first.
	cout << "Build a new sequenceFixed by inserting 30, 10, 20 (so the sequenceFixed\n";
	cout << "is 20, then 10, then 30). Then remove the 20." << endl;
	test.insert(30);
	test.insert(10);
	test.insert(20);
	test.remove_current();
	if (!correct(test, 2, 0, items2)) return 0;
	test.start();
	test.remove_current();
	test.remove_current();

	// Just for fun, fill up the sequenceFixed, and empty it!
	cout << "Just for fun, I'll empty the sequenceFixed then fill it up, then\n";
	cout << "empty it again. During this process, I'll try to determine\n";
	cout << "whether any of the sequenceFixed's member functions access the\n";
	cout << "array outside of its legal indexes." << endl;
	for (i = 0; i < test.CAPACITY; i++)
		test.insert(0);
	for (i = 0; i < test.CAPACITY; i++)
		test.remove_current();

	// Make sure that the character 'x' didn't somehow get into the sequenceFixed,
	// as that would indicate that the sequenceFixed member functions are
	// copying data from before or after the sequenceFixed into the sequenceFixed.
	char_ptr = (char *)&test;
	for (i = 0; i < sizeof(sequenceFixed); i++)
		if (char_ptr[i] == 'x')
		{
			cout << "Illegal array access detected." << endl;
			return POINTS[3] / 4;
		}

	// Make sure that the prefix and suffix arrays still have four
	// x's each. Otherwise one of the sequenceFixed operations wrote outside of
	// the legal boundaries of its array.
	for (i = 0; i < 4; i++)
		if ((suffix[i] != 'x') || (prefix[i] != 'x'))
		{
			cout << "Illegal array access detected." << endl;
			return POINTS[3] / 4;
		}

	// All tests passed
	cout << "All tests of this third function have been passed." << endl;
	return POINTS[3];
}

// **************************************************************************
// int test4( )
//   Performs a test to ensure that the erase_one(...) correctly removes
//   an item of the sequenceFixed. Returns POINTS[4] if the tests are passed. 
//   Otherwise returns 0.
// **************************************************************************
int test4()
{
	sequenceFixed testDup, testUnique;
	size_t i;
	// array of duplicate items
	int items3[3] = { 10, 10, 10 };
	size_t arrSize3 = sizeof(items3) / sizeof(int);
	// array of unique items
	int items5[5] = { 10, 20, 30, 40, 50 };
	size_t arrSize5 = sizeof(items5) / sizeof(int);

	// put items in the sequenceFixed of duplicates
	cout << "Attaching ";
	for (i = 0; i < arrSize3; i++) {
		cout << items3[i] << " ";
		testDup.attach(items3[i]);
	}
	cout << "to sequenceFixed of duplicate items." << endl;
	// try to erase item not found
	cout << "Attempting to erase item not in sequenceFixed...";
	if (testDup.erase_one(100)) {
		if (testDup.size() != arrSize3) {
			cout << "failed." << endl;
			return 0;
		}
	}
	cout << "passed." << endl;
	// remove items from sequenceFixed of duplicates
	cout << "Erasing duplicate items...";
	for (i = 0; i < arrSize3; i++)
		if (testDup.erase_one(items3[i]))
			// check size after removed
			if (testDup.size() + 1 != arrSize3 - i) {
				cout << "failed." << endl;
				return 0;
			}
	cout << "passed." << endl;

	// put items in the sequenceFixed of unique items
	cout << "Attaching " << endl;
	for (i = 0; i < arrSize5; i++) {
		cout << items5[i] << " ";
		testUnique.attach(items5[i]);
	}
	cout << "to sequenceFixed of unique items." << endl;
	// remove all items from non-duplicate array
	cout << "Erasing unique items...";
	for (i = 0; i < arrSize5; i++)
		if (testUnique.erase_one(items5[i]))
			// check size after removed
			if (testUnique.size() + 1 != arrSize5 - i) {
				cout << "failed." << endl;
				return 0;
			}
	cout << "passed." << endl;

	// All tests passed
	cout << "All tests of this fourth function have been passed." << endl;
	return POINTS[4];
}

int run_a_test(int number, const char message[], int test_function(), int max)
{
	int result;

	cout << endl << "START OF TEST " << number << ":" << endl;
	cout << message << " (" << max << " points)." << endl;
	result = test_function();
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
int main()
{
	int stuPoints[MANY_TESTS + 1] = { 0 }, sum = 0;

	cout << "Running " << DESCRIPTION[0] << endl;

	// run tests and identify points awarded
	stuPoints[1] = run_a_test(1, DESCRIPTION[1], test1, POINTS[1]);
	stuPoints[2] = run_a_test(2, DESCRIPTION[2], test2, POINTS[2]);
	stuPoints[3] = run_a_test(3, DESCRIPTION[3], test3, POINTS[3]);
	stuPoints[4] = run_a_test(4, DESCRIPTION[4], test4, POINTS[4]);

	// accumulate points
	for (int i = 1; i <= MANY_TESTS; i++)
		sum += stuPoints[i];

	// output testing results
	cout << "==========>TEST RESULTS<==========" << endl;
	cout << "If you submit the Chapter 3 sequenceFixed class now, you will have\n";
	cout << sum << " points out of the " << POINTS[0];
	cout << " points from this test program.\n";

	cout << "==========>POINT SUMMARY<==========" << endl;
	for (int i = 1; i <= MANY_TESTS; i++)
		cout << DESCRIPTION[i] << "\n\tPOINTS = " << stuPoints[i] << " out of " << POINTS[i] << endl;
	return EXIT_SUCCESS;
}

/*
==========>TEST RESULTS<==========
If you submit the Chapter 3 sequenceFixed class now, you will have
30 points out of the 30 points from this test program.
==========>POINT SUMMARY<==========
Testing insert, attach, and the constant member functions
		POINTS = 7 out of 7
Testing situations where the cursor goes off the sequenceFixed when using attach and remove_current member functions
		POINTS = 6 out of 6
Testing remove_current member function
		POINTS = 7 out of 7
Testing erase_one member function
		POINTS = 10 out of 10
*/
