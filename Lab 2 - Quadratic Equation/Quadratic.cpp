#include "Quadratic.h"
//default constructor
Quadratic::Quadratic() {
	a = 0;
	b = 0;
	c = 0;
}
//mutators s
void Quadratic::setA(double first) {
	a = first;
}
void Quadratic::setB(double second) {
	b = second;
}
void Quadratic::setC(double third) {
	c = third;
}
//accessors
double Quadratic::getA() const {
	return a;
}
double Quadratic::getB() const {
	return b;
}
double Quadratic::getC() const {
	return c;
}

//evaluate x multiplied expression

double Quadratic::evalQuadX(double x) {
	return ((a*(x*x)) + b * x + c);
}
//overload  +operator
//Precondition: coefficients have valid values
//Post condition: The return value is the
// quadratic expression obtained by
// adding each of the coefficients of
// the current object by each of the
// corresponding coefficients of q_rhs
// object. 
Quadratic Quadratic::operator +(const Quadratic& q_rhs) {
	Quadratic q;
	q.a = this->a + q_rhs.a;
	q.b = this->b + q_rhs.b;
	q.c = this->c + q_rhs.c;
	return q;
}
//overload *operator
//Precondition: coefficients have valid values
// Postcondition: The return value is the
// quadratic expression obtained by
// multiplying each of q’s coefficients
// by the number m.
Quadratic operator*(double m, const Quadratic& q_rhs) {
	Quadratic q;
	q.setA(q_rhs.getA()*m);
	q.setB(q_rhs.getB()*m);
	q.setC(q_rhs.getC()*m);
	return q;
}