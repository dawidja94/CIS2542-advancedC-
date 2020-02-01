// Lab #12 testing program for tableMultiChain
#include <iostream>
#include "tableMultiChain.h"
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

// testing function to remove keys from passed multiChain hash table
bool testCaseRemove(tableMultiChain<test_record_type>& mc, int key) {
	// determine number of duplicate keys using student defined method
	int removeCount = mc.count(key);
	cout << "\n\t-->removing " << removeCount << " links; KEY = " << key << endl;
	// display values for duplicate keys using student defined method
	mc.display_key_values(key);
	// calculate expected size once keys are removed
	int tableSize = mc.size() - removeCount;
	// remove values for duplicate keys using student defined method
	mc.remove_all(key);
	// compare expected and actual size
	if (tableSize == mc.size()) {
		cout << "\n\t-->SUCCESS: table size is now " << tableSize;
		return true;
	}
	else {
		cerr << "\n\t-->FAILURE: Improper removal of " << removeCount 
			<< " links; KEY = " << key << endl;
		return false;
	}
}

int main() {

	// identify hash keys and values
	int keys[] = { 4058, 3, 5678, 2, 811, 1, 2, 1, 1, 1623, 2435, 3 };
	int arrSize = sizeof(keys) / sizeof(int);
	double values[] = { 33.9, 33.1, 11.4, 22.1, 100, 11.1, 22.2, 11.2, 11.3, 11.0, 22.0, 33.2 };

	// build a chained hashTable to test
	tableMultiChain<test_record_type> hashTest;
	test_record_type trt;
	for (int i = 0; i < arrSize; i++) {
		trt.key = keys[i];
		trt.data = values[i];
		// insert values using student overridden method 
		// values added to end of current duplicate keys
		hashTest.insert(trt);
	}
	// display size and entries
	cout << "Starting table size is " << hashTest.size();
	hashTest.display_all();

	// remove no key 0 from index 0
	cout << "\n***TEST CASE #1***\n\t-->no matching key";
	if (testCaseRemove(hashTest, 0) == false)
		return EXIT_FAILURE;
	else
		hashTest.display_all();

	// remove only key 811 from index 0
	cout << "\n***TEST CASE #2***\n\t-->one matching key";
	if (testCaseRemove(hashTest, 811) == false)
		return EXIT_FAILURE;
	else
		hashTest.display_all();

	// remove 3 middle key duplicates from index 1
	cout << "\n***TEST CASE #3***\n\t-->three matching keys from middle";
	if (testCaseRemove(hashTest, 1) == false)
		return EXIT_FAILURE;
	else
		hashTest.display_all();

	// remove 2 last key duplicates from index 2
	cout << "\n***TEST CASE #4***\n\t-->two matching keys from end";
	if (testCaseRemove(hashTest, 2) == false)
		return EXIT_FAILURE;
	else
		hashTest.display_all();

	// remove 2 first key duplicates from index 3
	cout << "\n***TEST CASE #5***\n\t-->two matching keys from beginning";
	if (testCaseRemove(hashTest, 3) == false)
		return EXIT_FAILURE;
	else
		hashTest.display_all();

	return EXIT_SUCCESS;
}
