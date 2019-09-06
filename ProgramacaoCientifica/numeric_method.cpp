#include "pch.h"
#include "numeric_method.h"

int NumericMethod::factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double NumericMethod::df_dx_generic(std::function<double(double)>f, double x, int degrees)
{
	double sum = 0.0;
	double h = 0.0009;
	for (int i = 0; i <= degrees; i++)
	{
		double signal = pow(-1, i + degrees);
		double fat = (factorial(degrees) / (factorial(i) * factorial(degrees - i)));
		double result_f = f(x + (i * h));
		sum += (signal * (fat * result_f));
	}

	return sum / pow(h, degrees);
}

double NumericMethod::df_dx(std::function<double(double)>f, double x)
{
	return (f(x + _base_derivate_value) - f(x - _base_derivate_value)) / (2 * _base_derivate_value);
}

double NumericMethod::df_dx_2(std::function<double(double)>f, double x)
{
	return df_dx_generic(f, x, 2);
}

double NumericMethod::df_dx_3(std::function<double(double)>f, double x)
{
	return df_dx_generic(f, x, 3);
}

double NumericMethod::df_dx_4(std::function<double(double)>f, double x)
{
	return df_dx_generic(f, x, 4);
}

NumericMethod::NumericMethod(double interval_a, double interval_b)
{
	this->_a = interval_a;
	this->_b = interval_b;
}

NumericMethod::~NumericMethod()
{
}

// f(x) = x², x° = 2
double NumericMethod::gradient_descent_a(double x0, double beta, double epsilon)
{
	double function_i = pow(x0, 2); // x²
	double x_i = x0;

	while (function_i != 0 && function_i > epsilon)
	{
		double function_i_previous = function_i;
		double inclination = 2 * x_i; // 2x
		x_i = x_i - beta * inclination;
		function_i = 2 * x_i;

		if (function_i_previous == function_i) {
			break;
		}
	}

	if (function_i > epsilon || function_i < 0)
		cout << "Cannot ";

	cout << "Converge - Function_i: " << function_i << " X: " << x_i << endl;

	return x_i;
}

// f(x) = x³ - 2x² + 2, x° = 2
double NumericMethod::gradient_descent_b(double x0, double beta, double epsilon)
{
	double function_i = pow(x0, 3) - 2 * pow(x0, 2) + 2; // x³ - 2x² + 2
	double x_i = x0;

	while (function_i != 0 && function_i > epsilon)
	{
		double function_i_previous = function_i;
		double inclination = 3 * pow(x_i, 2) - 4 * x_i; // 3x² - 4x
		x_i = x_i - beta * inclination;
		function_i = 2 * x_i;

		if (function_i_previous == function_i) {
			break;
		}
	}

	if (function_i > epsilon || function_i < 0)
		cout << "Cannot ";

	cout << "Converge - Function_i: " << function_i << " X: " << x_i << endl;

	return x_i;
}

double NumericMethod::monte_carlo_class_6_f_2_by_attempts(std::function<double(double, double, double)> f, int attempts)
{
	srand(time(NULL));
	int count = 0;
	double result = 0.0;
	DynamicQueue<double> queue;

	while (count < attempts)
	{
		double x = (rand() % -1000 + 3000) / 1000.0; // (4 ->  1)
		double y = (rand() % -3000 + 3000) / 1000.0; // (4 -> -3)
		double z = (rand() % -1000 + 0000) / 1000.0; // (1 -> -1)

		double result_f = f(x, y, z);

		if (result_f <= 1 && x >= 1 && y >= -3) {
			queue.enqueue(result_f);
			count++;
		}
	}

	while (!queue.is_empty())
	{
		result += queue.dequeue();
	}

	return result / attempts;
}

double NumericMethod::monte_carlo_class_6_f_2_by_error_rate(std::function<double(double, double, double)> f, double error)
{
	double result = 0.0;
	double result_previous = 0.0;
	double error_numeric_method = error + 1;
	int attempts = 1;

	do
	{
		result_previous = result;
		result = monte_carlo_class_6_f_2_by_attempts(f, attempts);

		if (result == result_previous)
			break;

		error_numeric_method = monte_carlo_class_6_f_2_error(f, attempts);
		attempts++;
	} while (error_numeric_method > error);

	return result;
}

double NumericMethod::monte_carlo_class_6_f_2_error(std::function<double(double, double, double)> f, int attempts)
{
	srand(time(NULL));
	double f_error_square_result = 0.0;
	double f_error_result = 0.0;
	int count = 0;

	while (count < attempts)
	{
		double x = (rand() % 4000) / 1000.0;
		double y = (rand() % 4000) / 1000.0;
		double z = (rand() % 4000) / 1000.0;
		double f_result = f(x, y, z);

		f_error_square_result += pow(f_result, 2);
		f_error_result += f_result;

		count++;
	}

	return sqrt((f_error_square_result / attempts - pow((f_error_result / attempts), 2)) / attempts);
}

double NumericMethod::numeric_square_by_divisions(std::function<double(double)> f, std::function<double(std::function<double(double)>)> numeric_method_func, int divisions)
{
	double result = 0.0;
	double interval_a = _a;
	double interval_b = _b;
	int count = 0;
	double interval = (_b - _a) / divisions;
	DynamicQueue<double> queue;	

	while (count < divisions)
	{
		_b = _a + interval;
		queue.enqueue(numeric_method_func(f));
		_a += interval;
		count++;
	}

	while (!queue.is_empty())
	{
		result += queue.dequeue();
	}

	_a = interval_a;
	_b = interval_b;

	return result;
}

double NumericMethod::numeric_square_by_error_rate(std::function<double(double)> f, std::function<double(std::function<double(double)>)> numeric_method_func, std::function<double(std::function<double(double)>, int)> numeric_method_error_func, double error)
{
	double result = 0.0;
	double error_numeric_method = 0.0;
	int divisions = 0;

	do
	{
		divisions++;
		error_numeric_method = numeric_method_error_func(f, divisions);
	} while (error_numeric_method > error);

	result = numeric_square_by_divisions(f, numeric_method_func, divisions);

	cout << "Error: " << error_numeric_method << " - Divisions: " << divisions << " - ";

	return result;
}

double NumericMethod::midpoint(std::function<double(double)>f)
{
	return (_b - _a) * f((_a + _b) / 2);
}

double NumericMethod::trapezoidal(std::function<double(double)>f)
{
	return (_b - _a) * (f(_a) + f(_b)) / 2;
}

double NumericMethod::simpson(std::function<double(double)>f)
{
	return (_b - _a) * (f(_a) + (4 * (f((_a + _b) / 2))) + f(_b)) / 6;
}

double NumericMethod::monte_carlo_by_attempts(std::function<double(double)> f, int attempts)
{
	srand(time(NULL));
	int count = 0;
	double result = 0.0;
	DynamicQueue<double> queue;

	while (count < attempts)
	{
		double x = (rand() % 100) / 100.0;
		queue.enqueue(f(x));
		count++;
	}

	while (!queue.is_empty())
	{
		result += queue.dequeue();
	}

	return result / attempts;
}

double NumericMethod::monte_carlo_by_error_rate(std::function<double(double)> f, double error)
{
	double result = 0.0;
	double result_previous = 0.0;
	double error_numeric_method = error + 1;
	int attempts = 1;

	do
	{
		result_previous = result;
		result = monte_carlo_by_attempts(f, attempts);

		if (result == result_previous)
			break;

		error_numeric_method = monte_carlo_error(f, attempts);
		attempts++;
	} while (error_numeric_method > error);

	return result;
}

double NumericMethod::midpoint_error(std::function<double(double)>f, int divisions)
{
	return pow((_b - _a) / divisions, 3) / 24 * df_dx_2(f, (_b - _a) / 2);
}

double NumericMethod::trapezoidal_error(std::function<double(double)>f, int divisions)
{
	return -(pow((_b - _a) / divisions, 3) / 12) * df_dx_2(f, (_b - _a) / 2);
}

double NumericMethod::simpson_error(std::function<double(double)>f, int divisions)
{
	return -(pow((_b - _a) / divisions, 5) / 90) * df_dx_4(f, (_b - _a) / 2);
}

double NumericMethod::monte_carlo_error(std::function<double(double)> f, int attempts)
{
	srand(time(NULL));
	double f_error_square_result = 0.0;
	double f_error_result = 0.0;
	int count = 0;

	while (count < attempts)
	{
		double x = (rand() % 100) / 100.0;
		double f_result = f(x);

		f_error_square_result += pow(f_result, 2);
		f_error_result += f_result;

		count++;
	}

	return sqrt((f_error_square_result / attempts - pow((f_error_result / attempts), 2)) / attempts);
}

void NumericMethod::test_gradient()
{
	double beta = 0.1;
	double epsilon = 0.1;

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

void NumericMethod::test_adaptative_square()
{
	int divisions = 4;
	double error_rate = 0.05;
	Equations* eq = new Equations();

	/*cout << "Midpoint: " << midpoint(std::bind(&Equations::class_4_f_1, eq, _1)) << endl;
	cout << "Trapezoidal: " << trapezoidal(std::bind(&Equations::class_4_f_1, eq, _1)) << endl;
	cout << "Simpson: " << simpson(std::bind(&Equations::class_4_f_1, eq, _1)) << endl;*/

	/*cout << "Divisions: " << divisions << endl;
	cout << endl;

	cout << "f(x) = e^x" << endl;
	cout << "Midpoint: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), divisions) << endl;
	cout << "Trapezoidal: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), divisions) << endl;
	cout << "Simpson: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::simpson, this, _1), divisions) << endl;
	cout << endl;

	cout << "f(x) = square(1-x^2)" << endl;
	cout << "Midpoint: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), divisions) << endl;
	cout << "Trapezoidal: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), divisions) << endl;
	cout << "Simpson: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::simpson, this, _1), divisions) << endl;
	cout << endl;

	cout << "f(x) = e^(-x^2)" << endl;
	cout << "Midpoint: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), divisions) << endl;
	cout << "Trapezoidal: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), divisions) << endl;
	cout << "Simpson: " << adaptative_square_by_attempts(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::simpson, this, _1), divisions) << endl;*/

	cout << "Error rate: " << error_rate << endl;
	cout << endl;

	cout << "f(x) = e^x" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), std::bind(&NumericMethod::midpoint_error, this, _1, _2), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), std::bind(&NumericMethod::simpson, this, _1), std::bind(&NumericMethod::simpson_error, this, _1, _2), error_rate) << endl;
	cout << endl;

	cout << "f(x) = square(1-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), std::bind(&NumericMethod::midpoint_error, this, _1, _2), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), std::bind(&NumericMethod::simpson, this, _1), std::bind(&NumericMethod::simpson_error, this, _1, _2), error_rate) << endl;
	cout << endl;

	cout << "f(x) = e^(-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::midpoint, this, _1), std::bind(&NumericMethod::midpoint_error, this, _1, _2), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::trapezoidal, this, _1), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), std::bind(&NumericMethod::simpson, this, _1), std::bind(&NumericMethod::simpson_error, this, _1, _2), error_rate) << endl;
}

void NumericMethod::test_monte_carlo()
{
	int attempts = 10000;
	double error_rate = 0.05;
	Equations* eq = new Equations();

	cout << "Attempts: " << attempts << endl;
	cout << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_1, eq, _1), attempts) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_class_6_f_2_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1, _2, _3), attempts) << endl;

	/*cout << "Error rate: " << error_rate << endl;
	cout << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_error_rate(std::bind(&Equations::class_6_f_1, eq, _1), error_rate) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_class_6_f_2_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1, _2, _3), error_rate) << endl;*/
}