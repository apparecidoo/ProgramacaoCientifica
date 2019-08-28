#include <iostream>
#include <functional>
#include <time.h>

#include "queue_dynamic.h"
#include "equations.h"
#include "custom_exception.h"
#include "integrate_range.h"

#ifndef NUMERIC_METHOD_H
#define NUMERIC_METHOD_H

using namespace std;
using namespace std::placeholders;

class NumericMethod {

private:
	double _a = 0; // first number of interval integration 
	double _b = 1; // second number of interval integration
	double _base_derivate_value = 0.00000001; // minimum number to derivate

	int factorial(int n); // calculate factorial
	double df_dx_generic(std::function<double(double)>f, double x, int degrees); // calculate every derivative by degree
	double df_dx(std::function<double(double)>f, double x); // calculate first derivative
	double df_dx_2(std::function<double(double)>f, double x); // calculate second derivative
	double df_dx_3(std::function<double(double)>f, double x); // calculate third derivative
	double df_dx_4(std::function<double(double)>f, double x); // calculate fourth derivative

public:
	NumericMethod(double interval_a = 0, double interval_b = 1);
	~NumericMethod();

	static double gradient_descent_a(double x0, double beta, double epsilon); // calculate descent gradient of equation a (f(x) = x², x° = 2)
	static double gradient_descent_b(double x0, double beta, double epsilon); // calculate descent gradient of equation b (f(x) = x³ - 2x² + 2, x° = 2)
	
	double monte_carlo_class_6_f_2_by_attempts(std::function<double(double,double,double)>f, int attempts); // calculate monte carlo for equation of three variable and receiving attempts number
	double monte_carlo_class_6_f_2_by_error_rate(std::function<double(double, double, double)>f, double error); // calculate monte carlo for equation of three variable and error rate maximum
	double monte_carlo_class_6_f_2_error(std::function<double(double, double, double)>f, int attempts); // calculate monte carlo error for equation of three variable and receiving attempts number

	double midpoint(std::function<double(double)>f); // calculate midpoint for equation of one variable
	double trapezoidal(std::function<double(double)>f); // calculate trapezoidal for equation of one variable
	double simpson(std::function<double(double)>f); // calculate simpson for equation of one variable
	double numeric_square_by_divisions(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, int divisions); // calculate numeric square for equation of one variable, passing the method and number of divisions on integrate region
	double numeric_square_by_error_rate(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, std::function<double(std::function<double(double)>, int)> numeric_method_error_func, double error_rate); // calculate numeric square for equation of one variable, passing the method, method error and error rate maximum
	double monte_carlo_by_attempts(std::function<double(double)>f, int attempts); // calculate monte carlo for equation of one variable and receiving divisions number
	double monte_carlo_by_error_rate(std::function<double(double)>f, double error); // calculate monte carlo for equation of one variable and maximum error rate

	double midpoint_error(std::function<double(double)>f, int divisions); // calculate midpoint error for equation of one variable and receiving divisions number
	double trapezoidal_error(std::function<double(double)>f, int divisions); // calculate trapezoidal error for equation of one variable and receiving divisions number
	double simpson_error(std::function<double(double)>f, int divisions); // calculate simpson error for equation of one variable and receiving divisions number
	double monte_carlo_error(std::function<double(double)>f, int attempts); // calculate monte carlo error for equation of one variable and receiving attempts number

	void test_gradient(); // test for gradient
	void test_adaptative_square(); // test for adaptative square
	void test_monte_carlo(); // test for monte carlo
};

#endif
