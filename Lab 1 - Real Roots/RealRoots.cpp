/*
Author: Dawid Jasionowski
File:	RealRoots.cpp
Descr:
Create 2 functions to find real roots using assertion and exception
Date: 08/27/2018
*/


#include <iostream>
#include <cassert>

using namespace std;




//function prototypes
//Precondition: 0 > a > 0
void getRoot(double, double, double, double&, double&);
void rootExcept(double, double, double, double&, double&);




int main() {
	//Variables
	double a, b, c;
	double x1, x2;


	//Prompt user for A, B, and C values}
	cout << "Please enter a number for a: ";
	cin >> a;
	cout << "Please enter a number for b: ";
	cin >> b;
	cout << "Please enter a number for c: ";
	cin >> c;




	//getRoot(a, b, c, x1, x2);

	try {
		rootExcept(a, b, c, x1, x2);
	}
	catch (const invalid_argument& ex) {
		cerr << ex.what() << endl;
		exit(EXIT_FAILURE);
	}
	
	cout << "x1= " << x1 << endl;
	cout << "x2= " << x2 << endl;

	return (EXIT_SUCCESS);
}



//function to find real roots using assertion
//Precondition: a != 0, b*b > 4*a*c
//Postcondition: real roots for x1 and x2 are returned
void getRoot(double a, double b, double c, double& x1, double& x2) {

	assert(a != 0);
	assert(b*b > 4 * a*c);
	x1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	x2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);
}

//function to find real roots using exception
//Precondition: a != 0, b*b > 4*a*c
//Postcondition: real roots for x1 and x2 are returned
void rootExcept(double a, double b, double c, double& x1, double& x2) {


	if (a == 0 || b * b <= 4 * a *c)
		throw invalid_argument("ERROR! a = 0 or b*b <= 4 * a * c");
	else
	x1 = (-b + sqrt(b*b - 4 * a*c)) / (2 * a);
	x2 = (-b - sqrt(b*b - 4 * a*c)) / (2 * a);

}