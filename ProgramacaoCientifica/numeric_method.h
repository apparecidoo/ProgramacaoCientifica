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
	double _a = 0, _b = 1;
	double _base_derivate_value = 0.00000001;

	double df_dx(std::function<double(double)>f, double x);
	double df_dx_2(std::function<double(double)>f, double x);
	double df_dx_3(std::function<double(double)>f, double x);
	double df_dx_4(std::function<double(double)>f, double x);

public:
	NumericMethod(double interval_a = 0, double interval_b = 1);
	~NumericMethod();

	static double gradient_descent_a(double x_0, double beta, double epsilon);
	static double gradient_descent_b(double x_0, double beta, double epsilon);
	
	double monte_carlo_class_6_f_2_by_attempts(std::function<double(double,double,double)>f, int attempts);
	double monte_carlo_class_6_f_2_by_error_rate(std::function<double(double, double, double)>f, double error);
	double monte_carlo_class_6_f_2_error(std::function<double(double, double, double)>f, int attempts);

	double adaptative_square_by_divisions(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, int divisions);
	double adaptative_square_by_error_rate(std::function<double(double)>f, std::function<double(std::function<double(double)>)> numeric_method_func, std::function<double(std::function<double(double)>, int)> numeric_method_error_func, double error_rate);
	double midpoint(std::function<double(double)>f);
	double trapezoidal(std::function<double(double)>f);
	double simpson(std::function<double(double)>f);
	double monte_carlo_by_attempts(std::function<double(double)>f, int attempts);
	double monte_carlo_by_error_rate(std::function<double(double)>f, double error);

	double midpoint_error(std::function<double(double)>f, int divisions);
	double trapezoidal_error(std::function<double(double)>f, int divisions);
	double simpson_error(std::function<double(double)>f, int divisions);
	double monte_carlo_error(std::function<double(double)>f, int attempts);

	void test_gradient();
	void test_adaptative_square();
	void test_monte_carlo();
};

#endif
