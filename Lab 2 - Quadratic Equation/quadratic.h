#pragma once
#include<iostream>
using namespace std;
class Quadratic {
	//Member variables
private:
	double a;
	double b;
	double c;
	//Member functions
public:
	//default constructor
	Quadratic();
	//mutators
	void setA(double first);
	void setB(double second);
	void setC(double third);
	//accessors
	double getA() const;
	double getB() const;
	double getC() const;
	friend ostream &operator<<(ostream &out, const Quadratic &quad);
	double evalQuadX(double);



	//overload+ operator
	Quadratic operator +(const Quadratic& q_rhs);

	//overload* operator
	friend Quadratic operator*(double m, const Quadratic& q_rhs);
};

