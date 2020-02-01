// File: Lab2.cpp
// Desc: A program which asks user to input values for a quadratic
//		expression before returning that expression and evaluating
//		the expression for a user input value of x. It then asks
//		the user to add a value to the expression and multiply the
//		expression by a certain value, both chosen by the user.

#include "Quadratic.h"


// overloading output as non-member and non-friend function
std::ostream& operator <<(std::ostream& out, const Quadratic& quad)
// Postcondition: The a, b, and c coefficients have been written to outs in quadratic form.  The return value is output.
// Library facilities used: iostream
{
	out << quad.getA() << "x^2 + " << quad.getB() << "x + " << quad.getC() << endl;
	return out;
}

// create and display a quadratic expression
void createQuad(Quadratic &quad) {
	double a, b, c;
	cout << "\ta: ";
	cin >> a;
	cout << "\tb: ";
	cin >> b;
	cout << "\tc: ";
	cin >> c;
	quad.setA(a);
	quad.setB(b);
	quad.setC(c);
	cout << "\n The quadratic expression is: \n" << quad << endl;
	quad.setC(c);
	cout << "\n The quadratic expression is: \n" << quad << endl;
}
int main()
{
	double x, multiplier;
	Quadratic eq1, eq2, eq1a2, eq1m;
	// create first quadratic


	cout << "Input the values for the first quaratic expression." << endl;
	createQuad(eq1);
	cout << "Enter a value for x: ";
	cin >> x;
	cout << "Evaluation of the quadratic expression is: " << eq1.evalQuadX(x) << endl;


	//create second quadratic to add with first
	cout << "\n Input the values for the second quadratic expression\n\t to add to the first." << endl;
	createQuad(eq2);
	eq1a2 = eq1 + eq2;
	cout << "Added quadratic expression is: " << eq1a2 << endl;
	cout << "Enter a value for x: ";
	cin >> x;
	cout << "Evaluation of the quadratic expression is: " << eq1a2.evalQuadX(x) << endl;
	//create third quadratic to multiply with first
	cout << "\nInput the multiplier value for the third quadratic expression\n\t to multiply with the first: ";
	cin >> multiplier;
	eq1m = multiplier * eq1;
	cout << "Multiplied quadratic expression is: " << eq1m << endl;
	cout << "Enter a value for x: ";
	cin >> x;
	cout << "Evaluation of the quadratic expression is: " << eq1m.evalQuadX(x) << endl;
	return EXIT_SUCCESS;
}



/*
Sample run
Input the values for the first quaratic expression.
		a: 3.2
		b: 5.5
		c: 1.7

 The quadratic expression is:
3.2X^2+ 5.5X+ 1.7


 The quadratic expression is:
3.2X^2+ 5.5X+ 1.7

Enter a value for x: 2
Evaluation of the quadratic expression is: 25.5

 Input the values for the second quadratic expression
		 to add to the first.
		a: 1.8
		b: 5
		c: 3.2

 The quadratic expression is:
1.8X^2+ 5X+ 3.2


 The quadratic expression is:
1.8X^2+ 5X+ 3.2

Added quadratic expression is: 5X^2+ 10.5X+ 4.9

Enter a value for x: 3.5
Evaluation of the quadratic expression is: 102.9

Input the multiplier value for the third quadratic expression
		 to multiply with the first: 7.7
Multiplied quadratic expression is: 24.64X^2+ 42.35X+ 13.09

Enter a value for x: 8.1
Evaluation of the quadratic expression is: 1972.76

*/