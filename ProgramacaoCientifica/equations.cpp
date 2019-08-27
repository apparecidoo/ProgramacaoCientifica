#include "pch.h"
#include "equations.h"

Equations::Equations()
{
}

Equations::~Equations()
{
}

double Equations::class_5_f_1(double x)
{
	return exp(x); // f(x) = e^x
}

double Equations::class_5_f_2(double x)
{
	return sqrt(1 - pow(x, 2)); // f(x) = square(1-x²)
}

double Equations::class_5_f_3(double x)
{
	return exp(-pow(x, 2)); // f(x) = e^-x²
}

double Equations::class_6_f_1(double x)
{
	return 4 / (1 + pow(x, 2));  // f(x) = 4 / (1 + x²)
}

double Equations::class_6_f_2(double x, double y, double z)
{
	return pow(z, 2) + pow(sqrt(pow(x, 2) + pow(y, 2) - 3), 2); // f(x) = -z² + (square(x²+y²) - 3)²
}
