// FILE:  RecListTesting.cpp
// DESCR: 
// Testing program for recursive
// template list functions of 
// CIS2542 Lab #9.

#include <iostream>
#include "nodeTemplate.h"    // instructor provided files
#include "recListToolkit.h"  // student created file

using namespace std;

int main() {
	// identify node values
	double ditems[] = { 5.5, 33.3, 22.2, 77.7, 11.1
	};
	int arrSize = sizeof(ditems) / sizeof(double);

	// create linked list
	nodeTemplate<double>* head_ptr = nullptr;  // empty list
	// add items to list
	for (int i = 0; i < arrSize; i++) {
		list_head_insert(head_ptr, ditems[i]);
	}

	// recursive count of list items
	cout << "The number of items in list is " << rec_list_length(head_ptr) << endl;

	// recursive list display 
	cout << "List items in order:" << endl;
	rec_display_list(head_ptr);
	cout << "List items in reverse order:" << endl;
	rev_display_list(head_ptr);

	// recursive search
	double dval;
	cout << "\nSearching with recursive function..." << endl;
	cout << "Input a  value to search (0 to end): ";
	cin >> dval;
	while (dval != 0.0) {
		nodeTemplate<double>* toFind = rec_list_search(head_ptr, dval);
		if (toFind != nullptr)
			cout << toFind->data() << " has been found!" << endl;
		else cout << dval << " has NOT been found!" << endl;
		cout << "Input a  value to search (0 to end): ";
		cin >> dval;
	}

	// recursively release the memory
	rec_list_clear(head_ptr);

	return EXIT_SUCCESS;
}