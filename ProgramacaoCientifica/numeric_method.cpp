#include "pch.h"
#include "numeric_method.h"
#include "custom_exception.h"

double NumericMethod::df_dx(double x)
{
	return (f_x(x + _base_derivate_value) - f_x(x - _base_derivate_value)) / (2 * _base_derivate_value);
}

double NumericMethod::df_dx_2(double x)
{
	return 0.0;
}

double NumericMethod::df_dx_3(double x)
{
	return 0.0;
}

double NumericMethod::df_dx_4(double x)
{
	return 0.0;
}

NumericMethod::NumericMethod(double interval_a, double interval_b, std::function<double(double)> f)
{
	this->_a = interval_a;
	this->_b = interval_b;
	this->f_x = f;
}

NumericMethod::~NumericMethod()
{
}

// f(x) = x², x° = 2
double NumericMethod::gradient_descent_a(double x_0, double beta, double epsilon)
{
	double function_i = pow(x_0, 2); // x²
	double x_i = x_0;

	while (function_i != 0 && function_i > epsilon)
	{
		double function_i_previous = function_i;
		double inclination = 2 * x_i; // 2x
		x_i = x_i - beta * inclination;
		function_i = 2 * x_i;

		if (function_i_previous == function_i) {
			cout << "Cannot converged - X: " << x_i << endl;
			return x_i;
		}
	}

	cout << "Value X: " << x_i << endl;

	return x_i;
}

// f(x) = x³ - 2x² + 2, x° = 2
double NumericMethod::gradient_descent_b(double x_0, double beta, double epsilon)
{
	double function_i = pow(x_0, 3) - 2 * pow(x_0, 2) + 2; // x³ - 2x² + 2
	double x_i = x_0;

	while (function_i != 0 && function_i > epsilon)
	{
		double function_i_previous = function_i;
		double inclination = 3 * pow(x_i, 2) - 4 * x_i; // 3x² - 4x
		x_i = x_i - beta * inclination;
		function_i = 2 * x_i;

		if (function_i_previous == function_i) {
			cout << "Cannot converge - X: " << x_i << endl;
			return x_i;
		}
	}

	cout << "Value X: " << x_i << endl;

	return x_i;
}

double NumericMethod::Midpoint()
{
	if (f_x == NULL)
		throw CustomException("The function not found");

	return (_b - _a) * f_x((_a + _b) / 2);
}

double NumericMethod::Midpoint(double(*f)(double))
{
	return (_b - _a) * f((_a + _b) / 2);
}

double NumericMethod::Trapezoidal()
{
	if (f_x == NULL)
		throw CustomException("The function not found");

	return (_b - _a) * (f_x(_a) + f_x(_b)) / 2;
}

double NumericMethod::Trapezoidal(double(*f)(double))
{
	return (_b - _a) * (f(_a) + f(_b)) / 2;
}

double NumericMethod::Simpson()
{
	if (f_x == NULL)
		throw CustomException("The function not found");

	return (_b - _a) * (f_x(_a) + (4 * (f_x((_a + _b) / 2 ))) + f_x(_b)) / 6;
}

double NumericMethod::Simpson(double(*f)(double))
{
	return (_b - _a) * (f(_a) + (4 * (f((_a + _b) / 2))) + f(_b)) / 6;
}

double NumericMethod::MidpointError()
{
	return -pow((_b - _a), 3) / 24 * df_dx_2((_b - _a) / 2);
}

double NumericMethod::TrapezoidalError()
{
	return -pow((_b - _a), 3) / 12 * df_dx_2((_b - _a) / 2);
}

double NumericMethod::simpson_error()
{
	return -pow((_b - _a), 5) / 2880 * df_dx_4((_b - _a) / 2);
}

void NumericMethod::test_gradient()
{
	double beta = 0.1;
	double epsilon = 0.000000000001;

	cout << "f(x) = x^2" << endl;
	while (beta <= 1)
	{
		cout << "Beta = " << beta << endl;
		this->gradient_descent_a(2, beta, epsilon);
		beta += 0.1;
		cout << endl;
	}

	cout << endl << "f(x) = x^3 - 2x^2 + 2" << endl;
	beta = 0.1;
	while (beta <= 1)
	{
		cout << "Beta = " << beta << endl;
		this->gradient_descent_b(2, beta, epsilon);
		beta += 0.1;
		cout << endl;
	}
}
