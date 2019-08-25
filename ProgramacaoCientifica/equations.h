#include <iostream>

#ifndef EQUATIONS_H
#define EQUATIONS_H

using namespace std;

// Contains examples of equations to be solved, classified by class
class Equations {
public:
	Equations();
	~Equations();

	double class_4_f_1(double x); // f(x) = e^x
	double class_4_f_2(double x); // f(x) = raiz(1-x²)
	double class_4_f_3(double x); // f(x) = e^-x²
};

#endif
