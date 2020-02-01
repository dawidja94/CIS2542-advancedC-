#include <iostream>
#include "tableChain.h"
using namespace std;

// Struct definition for the test_record_type, which has a key and a double.
struct test_record_type
{
	int key;
	double data;
};

// overload output operator for display method
ostream& operator <<(ostream& outs, const test_record_type& source) {
	outs << "KEY=" << source.key << " DATA=" << source.data;
	return outs;
}

int main() {

	// identify hash keys and values
	int keys[] = { 4058, 2, 1, 811, 1623, 2435, 3245, 5678, 3 };
	int arrSize = sizeof(keys) / sizeof(int), toRemove, tableSize;
	double values[] = { 33.2, 22.2, 11.4, 100, 11.3, 22.1, 11.2, 11.1, 33.1 };

	// build a chained hashTable to test
	tableChain<test_record_type> hashTest;
	test_record_type trt;
	for (int i = 0; i < arrSize; i++) {
		trt.key = keys[i];
		trt.data = values[i];
		hashTest.insert(trt);
	}
	// display size and entries
	tableSize = hashTest.size();
	cout << "The table size is " << tableSize;
	hashTest.display_all();

	// remove no key 0 from index 0
	toRemove = 0;
	cout << "\n-->removing no link: key " << toRemove << endl;
	hashTest.remove(toRemove);
	if (tableSize == hashTest.size()) {
		cout << "-->SUCCESS: no change in size " << tableSize << endl;
	}
	else {
		cerr << "-->FAILURE: Improper removal of no link: key " << toRemove << endl;
		return EXIT_FAILURE;
	}

	// remove only key 811 from index 0
	toRemove = 811;
	cout << "\n-->removing only link: key " << toRemove << endl;
	hashTest.remove(toRemove);
	if (--tableSize == hashTest.size()) {
		cout << "-->SUCCESS: table size is " << tableSize;
		hashTest.display_all();
	}
	else {
		cerr << "-->FAILURE: Improper removal of only link: key " << toRemove << endl;
		return EXIT_FAILURE;
	}

	// remove middle key 3245 from index 1
	toRemove = 3245;
	cout << "\n-->removing middle link: " << toRemove << endl;
	hashTest.remove(toRemove);
	if (--tableSize == hashTest.size()) {
		cout << "-->SUCCESS: table size is " << tableSize;
		hashTest.display_all();
	}
	else {
		cerr << "-->FAILURE: Improper removal of middle link: key " << toRemove << endl;
		return EXIT_FAILURE;
	}

	// remove last key 2 from index 2
	toRemove = 2;
	cout << "\n-->removing last link: key " << toRemove << endl;
	hashTest.remove(toRemove);
	if (--tableSize == hashTest.size()) {
		cout << "-->SUCCESS: table size is " << tableSize;
		hashTest.display_all();
	}
	else {
		cerr << "-->FAILURE: Improper removal of last link: key " << toRemove << endl;
		return EXIT_FAILURE;
	}

	// remove first key 3 from index 3
	toRemove = 3;
	cout << "\n-->removing first link: key " << toRemove << endl;
	hashTest.remove(toRemove);
	if (--tableSize == hashTest.size()) {
		cout << "-->SUCCESS: table size is " << tableSize;
		hashTest.display_all();
	}
	else {
		cerr << "-->FAILURE: Improper removal of first link: key " << toRemove << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
