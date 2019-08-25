#include <iostream>
#include <functional>

#ifndef NUMERIC_METHOD_H
#define NUMERIC_METHOD_H

using namespace std;

class NumericMethod {

private:
	double _a = 0, _b = 1;
	double _base_derivate_value = 0.00000001;

	double df_dx(double x);
	double df_dx_2(double x);
	double df_dx_3(double x);
	double df_dx_4(double x);

	std::function<double(double)> f_x = NULL;

public:
	NumericMethod(double interval_a = 0, double interval_b = 1, std::function<double(double)> f = NULL);
	~NumericMethod();

	static double gradient_descent_a(double x_0, double beta, double epsilon);
	static double gradient_descent_b(double x_0, double beta, double epsilon);

	double Midpoint();
	double Midpoint(double(*f)(double));
	double Trapezoidal();
	double Trapezoidal(double(*f)(double));
	double Simpson();
	double Simpson(double(*f)(double));

	double MidpointError();
	double TrapezoidalError();
	double simpson_error();

	void test_gradient();
};

#endif
