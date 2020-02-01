
// File: expressionTree_test.cpp
// Desc: This program tests the implementation
//       of a postfix evaluation tree consisting of
//       integers and the * and + operators.

#include "expressionTree.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// recursively displays binary expression tree
void expTreePrint(const expTreeNode* node_ptr, int depth = 5) {
	cout << setw(4 * depth) << ""; // indentation
	if (node_ptr == nullptr) {
		// fallen off the tree
		cout << "[Empty]" << std::endl;
	}
	else if (node_ptr->left_field == nullptr) {
		// a leaf with numeric data
		cout << node_ptr->number;
		cout << " [leaf]" << std::endl;
	}
	else {
		// a nonleaf with operator
		cout << node_ptr->op << std::endl;
		expTreePrint(node_ptr->right_field, depth + 1);
		expTreePrint(node_ptr->left_field, depth + 1);
	}
}

// testing function
int main() {
	// create testcases
	string testCases[] = { ".5 .25 /\n",
		"2.5 3.7 + 8.5 *\n", "5 3.1 2 * + 4 - 5 +\n",
		"25 347.8 5 * + 5 /\n", "2 3 /\n" };
	double testResults[] = { 2, 52.7, 12.2, 352.8, 0.666667 };
	int numTests = sizeof(testResults) / sizeof(double);
	// loop for all test cases
	for (int index = 0; index < numTests; ++index) {
		expressionTree *expTree = new expressionTree(testCases[index]);
		// display binary tree
		expTreePrint(expTree->get_root());
		cout << "Postfix expression: " << testCases[index]
			<< "\n\t==> evaluates to " << evaluate(expTree->get_root())
			<< "\n\t==> correct answer is " << testResults[index] << endl;
		// release memory
		delete expTree;
	}
	return EXIT_SUCCESS;
}