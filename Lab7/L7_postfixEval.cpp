//Author:	Dawid Jasionowski
//Date:		10/19/2018
//File:		L7_postifixEval.cpp
//Descr:
// Reads a series of postfix notation equations from the user,
// processes them into a stack, evaluates them, then presents the value to
// the user.  

#include <iostream>
#include <string>
#include <stack>        // STL stack class
#include <cstdlib>      // Provides EXIT_SUCCESS
#include <cassert>      // Provides assert
#include <cctype>
#include <sstream>
using namespace std;

double eval(double op1, double op2, char op)
{
	double result;
	assert(op1 >= 0); //make sure non-negative numbers were entered
	assert(op2 >= 0);
	switch (op) {
	case '+':
		result = op1 + op2;
		break;
	case '-':
		result = op1 - op2;
		break;
	case '*':
		result = op1 * op2;
		break;
	case '/':
		assert( op2 != 0);
			result = op1 / op2;
			break;
	}

	return result;
}

// Precondition: input string is valid and has data to process
// Postcondition: input string is processed as postfix arithmetic
// expression made up of nonnegative double numbers and the
// four operations + - * and /. STL Stack holds nonnegative
// double numbers for evaluation.  If everything went okay, then
// the return value answer is set to the value of this 
// expression.  Evaluation algorithm found in Figure 7.10 of 
// textbook or Lecture Slide 18
double evalPostfix(string& input) {
	
	stack<double> values;
	stringstream ss{ input };

	char op;
	double value;

	for (;;) {// infinite loop 
		streampos pos;
		//extract numbers from stringstream
		for (;;) {
			pos = ss.tellg(); //return to current character
			if (!(ss >> value))
				break;
			values.push(value);
		}

		ss.clear();
		ss.seekg(pos); // go to next character in stream

		if (!(ss >> skipws >> op)) // try to extract from stream, break the loop if fails
			break;

		
		// if operation is not + - * /
		if (op != '+' && op != '-' && op != '*' && op != '/') {
			cerr << '\'' << op << "' is not a valid operator!\n";
			
		}

		assert(values.size() >= 2);

		double op2 = values.top();
		values.pop();
		double op1 = values.top();
		values.pop();
		values.push(eval(op1, op2, op)); // push result into the stack
	}

	assert(values.size() <= 1);

	return values.top();
}

// main controlling function
int main() {
	double answer;
	string exp;
	cout << "Enter the postfix expression: ";
	getline(cin, exp);
	while (exp.length() > 0) {
		answer = evalPostfix(exp);
		cout << "==> evaluates to " << answer << endl;
		cout << "Enter another postfix expression or <CR> to end: ";
		getline(cin, exp);
	}
	return EXIT_SUCCESS;
}

/*
sample output
Enter the postfix expression: .5 .25 /
==> evaluates to 2
Enter another postfix expression or <CR> to end: 2.5 3.7 + 8.5 *
==> evaluates to 52.7
Enter another postfix expression or <CR> to end: 5 3.1 2 * + 4 - 5 +
==> evaluates to 12.2
Enter another postfix expression or <CR> to end: 25 347.8 5 * + 5 /
==> evaluates to 352.8
Enter another postfix expression or <CR> to end: 2 3 /
==> evaluates to 0.666667
Enter another postfix expression or <CR> to end:

*/