#include "pch.h"
#include "equations.h"

Equations::Equations()
{
}

Equations::~Equations()
{
}

double Equations::class_4_f_1(double x)
{
	return exp(x); // f(x) = e^x
}

double Equations::class_4_f_2(double x)
{
	return sqrt(1 - pow(x, 2)); // f(x) = square(1-x²)
}

double Equations::class_4_f_3(double x)
{
	return exp(pow(-x, 2)); // f(x) = e^-x²
}
