#include <iostream>
#include <math.h>

#ifndef EQUATIONS_H
#define EQUATIONS_H

using namespace std;

// Contains examples of equations to be solved, classified by class
class Equations {
public:
	Equations();
	~Equations();

	double class_5_f_1(double x); // f(x) = e^x
	double class_5_f_2(double x); // f(x) = raiz(1-x²)
	double class_5_f_3(double x); // f(x) = e^-x²
	double class_6_f_1(double x); // f(x) = 4 / (1 + x²)
	double class_6_f_2(double x, double y, double z); // f(x) = -z² + (square(x²+y²) - 3)²
};

#endif
