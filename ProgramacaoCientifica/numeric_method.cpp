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

NumericMethod::NumericMethod()
{
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

double NumericMethod::monte_carlo_volume_error(std::function<double(double, double, double)> f, IntegrateRange<double>* ranges, int attempts)
{
	double f_error_square_result = 0.0;
	double f_error_result = 0.0;
	int count = 0;
	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(ranges[0].a, ranges[0].b);
	uniform_real_distribution<double> distr_y(ranges[1].a, ranges[1].b);
	uniform_real_distribution<double> distr_z(ranges[2].a, ranges[2].b);

	while (count < attempts)
	{
		double x = distr_x(eng);
		double y = distr_y(eng);
		double z = distr_z(eng);
		double f_result = f(x, y, z);

		f_error_square_result += pow(f_result, 2);
		f_error_result += f_result;

		count++;
	}

	return sqrt((f_error_square_result / attempts - pow((f_error_result / attempts), 2)) / attempts);
}

double NumericMethod::numeric_square_by_divisions(std::function<double(double)> f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, int divisions)
{
	auto start = std::chrono::high_resolution_clock::now();
	double result = 0.0;
	double interval_a = range.a;
	double interval_b = range.b;
	int count = 0;
	double interval = (interval_b - interval_a) / divisions;

	while (count < divisions)
	{
		interval_b = interval_a + interval;
		result += numeric_method_func(f, IntegrateRange<double>(interval_a, interval_b));
		interval_a += interval;
		count++;
	}

	cout << "Executed in Time in seconds: " << duration_cast<duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << endl;

	return result;
}

double NumericMethod::numeric_square_by_error_rate(std::function<double(double)> f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, std::function<double(std::function<double(double)>, IntegrateRange<double>, int)> numeric_method_error_func, double error_rate)
{
	double result = 0.0;
	double error_numeric_method = 0.0;
	int divisions = 0;

	do
	{
		divisions++;
		error_numeric_method = numeric_method_error_func(f, range, divisions);
	} while (error_numeric_method > error_rate);

	result = numeric_square_by_divisions(f, range, numeric_method_func, divisions);

	cout << "Error: " << error_numeric_method << " - Divisions: " << divisions << " - ";

	return result;
}

double NumericMethod::midpoint(std::function<double(double)>f, IntegrateRange<double> range)
{
	return (range.b - range.a) * f((range.a + range.b) / 2);
}

double NumericMethod::trapezoidal(std::function<double(double)>f, IntegrateRange<double> range)
{
	return (range.b - range.a) * (f(range.a) + f(range.b)) / 2;
}

double NumericMethod::simpson(std::function<double(double)>f, IntegrateRange<double> range)
{
	return (range.b - range.a) * (f(range.a) + (4 * (f((range.a + range.b) / 2))) + f(range.b)) / 6;
}

double NumericMethod::monte_carlo_by_attempts(std::function<double(double)> f, IntegrateRange<double> range, int attempts)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(range.a, range.b);
	int count = 0;
	double result = 0.0;

	while (count < attempts)
	{
		double x = distr_x(eng);
		result += f(x);
		count++;
	}

	return result / attempts;
}

void NumericMethod::monte_carlo_by_attempts_distributed(std::function<double(double)> f, IntegrateRange<double> range, int attempts)
{
	int i;
	int id;
	int ierr;
	int master = 0;
	int number_process;
	double wtime_start;
	double result = 0.0;
	double result_part = 0.0;

	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(range.a, range.b);

	ierr = MPI_Init(NULL, NULL); // Initialize MPI.
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &number_process); // Get the number of processes
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id); // Determine this processes's rank

	if (id == master)
	{
		cout << "MONTE CARLO - Master process: The number of processes available is " << number_process << endl;
		cout << "MONTE CARLO - Attempts: " << attempts << endl;
		wtime_start = MPI_Wtime(); // Record the starting time
	}

	ierr = MPI_Bcast(&attempts, 1, MPI_INT, master, MPI_COMM_WORLD); // The master process broadcasts, and the other processes receive, the number of intervals attempts

	// Coding
	/*cout << "MONTE CARLO - Process " << id << endl;
	cout << "  Start Range " << attempts / number_process * id << endl;*/
	for (i = (attempts / number_process * id); i < (attempts / number_process * (id + 1)); i++)
	{
		double x = distr_x(eng);
		result_part += f(x);
	}
	/*cout << "  End Range " << attempts / number_process * (id + 1) << endl;
	cout << "  Estimate " << result_part << endl;*/

	ierr = MPI_Reduce(&result_part, &result, 1, MPI_DOUBLE, MPI_SUM, master, MPI_COMM_WORLD); // Each process sends its local result result_part to the MASTER process, to be added to the global result.

	// The master process scales the sum and reports the results.
	if (id == master)
	{
		//MPI_Barrier(MPI_COMM_WORLD);
		cout << "MONTE CARLO - Master process: Integral value is " << result / attempts << endl;
		cout << "MONTE CARLO - Wall clock elapsed seconds: " << MPI_Wtime() - wtime_start << endl;
	}

	ierr = MPI_Finalize(); // Terminate MPI

	/*if (id == master) {
		cout << endl << "MONTE CARLO - Master process: Normal end of execution." << endl;
	}*/
}

double NumericMethod::numeric_square_by_divisions_distributed(std::function<double(double)> f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, int divisions)
{
	int nprocs = omp_get_num_procs();
	omp_set_num_threads(nprocs);
	auto start = std::chrono::high_resolution_clock::now();

	double result = 0.0;
	double interval_a = 0.0;
	double interval_b = 0.0;
	int count = 0;

#if IS_PARALLEL == 1
#pragma omp parallel for reduction(+:result) private(interval_a, interval_b)
#endif
	for (count = 0; count < divisions; count++)
	{
		interval_a = (count * (range.b - range.a) / divisions) + range.a;
		interval_b = ((count + 1) * (range.b - range.a) / divisions) + range.a;

		result += numeric_method_func(f, IntegrateRange<double>(interval_a, interval_b));
	}

	cout << "Executed in Time in seconds: " << duration_cast<duration<double>>(std::chrono::high_resolution_clock::now() - start).count() << endl;

	return result;
}

double NumericMethod::numeric_square_by_error_rate_distributed(std::function<double(double)> f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, std::function<double(std::function<double(double)>, IntegrateRange<double>, int)> numeric_method_error_func, double error_rate)
{
	int nprocs = omp_get_num_procs();
	omp_set_num_threads(nprocs);
	double start_time = omp_get_wtime();

	double result = 0.0;
	double error_numeric_method = error_rate + 1.0;
	int divisions = 0;

//#if IS_PARALLEL == 1
//#pragma omp parallel for reduction(+:result) private(error_numeric_method) shared(divisions)
//#endif
	for (divisions = 0; error_numeric_method > error_rate; divisions++)
	{
		error_numeric_method = numeric_method_error_func(f, range, divisions);
	}

	result = numeric_square_by_divisions(f, range, numeric_method_func, divisions);
	
	cout << "Error: " << error_numeric_method << " - Divisions: " << divisions << " - ";

	return result;
}

double NumericMethod::monte_carlo_by_error_rate(std::function<double(double)> f, IntegrateRange<double> range, double error)
{
	double result = 0.0;
	double result_previous = 0.0;
	double error_numeric_method = error + 1;
	int attempts = 1;

	do
	{
		result_previous = result;
		result = monte_carlo_by_attempts(f, range, attempts);

		if (result == result_previous)
			break;

		error_numeric_method = monte_carlo_error(f, range, attempts);
		attempts++;
	} while (error_numeric_method > error);

	return result;
}

double NumericMethod::monte_carlo_volume_by_attempts(std::function<double(double, double, double)> f, IntegrateRange<double>* ranges, int attempts)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(ranges[0].a, ranges[0].b);
	uniform_real_distribution<double> distr_y(ranges[1].a, ranges[1].b);
	uniform_real_distribution<double> distr_z(ranges[2].a, ranges[2].b);

	int count = 0;
	double result = 0.0;
	double delta_x = ranges[0].b - ranges[0].a;
	double delta_y = ranges[1].b - ranges[1].a;
	double delta_z = ranges[2].b - ranges[2].a;
	double base_volume = delta_x * delta_y * delta_z;

	while (count < attempts)
	{
		double x = distr_x(eng);
		double y = distr_y(eng);
		double z = distr_z(eng);

		double result_f = f(x, y, z);

		if (result_f <= 1 && x >= 1 && y >= -3) {
			result += result_f;
			count++;
		}
	}

	return base_volume * result / attempts;
}

void NumericMethod::monte_carlo_volume_by_attempts_distributed(std::function<double(double, double, double)> f, IntegrateRange<double>* ranges, int attempts)
{
	int i;
	int id;
	int ierr;
	int master = 0;
	int number_process;
	double wtime_start;
	double result = 0.0;
	double result_part = 0.0;

	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(ranges[0].a, ranges[0].b);
	uniform_real_distribution<double> distr_y(ranges[1].a, ranges[1].b);
	uniform_real_distribution<double> distr_z(ranges[2].a, ranges[2].b);
	double delta_x = ranges[0].b - ranges[0].a;
	double delta_y = ranges[1].b - ranges[1].a;
	double delta_z = ranges[2].b - ranges[2].a;
	double base_volume = delta_x * delta_y * delta_z;

	ierr = MPI_Init(NULL, NULL); // Initialize MPI.
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &number_process); // Get the number of processes
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id); // Determine this processes's rank

	if (id == master)
	{
		cout << "MONTE CARLO - Master process: The number of processes available is " << number_process << endl;
		cout << "MONTE CARLO - Attempts: " << attempts << endl;
		wtime_start = MPI_Wtime(); // Record the starting time
	}

	ierr = MPI_Bcast(&attempts, 1, MPI_INT, master, MPI_COMM_WORLD); // The master process broadcasts, and the other processes receive, the number of intervals attempts

	// Coding
	/*cout << "MONTE CARLO - Process " << id << endl;
	cout << "  Start Range " << attempts / number_process * id << endl;*/
	for (i = (attempts / number_process * id); i < (attempts / number_process * (id + 1)); )
	{
		double x = distr_x(eng);
		double y = distr_y(eng);
		double z = distr_z(eng);

		double result_f = f(x, y, z);

		if (result_f <= 1 && x >= 1 && y >= -3) {
			result_part += result_f;
			i++;
		}
	}
	/*cout << "  End Range " << attempts / number_process * (id + 1) << endl;
	cout << "  Estimate " << result_part << endl;*/

	ierr = MPI_Reduce(&result_part, &result, 1, MPI_DOUBLE, MPI_SUM, master, MPI_COMM_WORLD); // Each process sends its local result result_part to the MASTER process, to be added to the global result.

	// The master process scales the sum and reports the results.
	if (id == master)
	{
		//MPI_Barrier(MPI_COMM_WORLD);
		cout << "MONTE CARLO - Master process: Volume of Integral value is " << base_volume * result / attempts << endl;
		cout << "MONTE CARLO - Wall clock elapsed seconds: " << MPI_Wtime() - wtime_start << endl;
	}

	ierr = MPI_Finalize(); // Terminate MPI

	/*if (id == master) {
		cout << endl << "MONTE CARLO - Master process: Normal end of execution." << endl;
	}*/
}

double NumericMethod::monte_carlo_volume_error_rate(std::function<double(double, double, double)> f, IntegrateRange<double>* ranges, double error)
{
	double result = 0.0;
	double result_previous = 0.0;
	double error_numeric_method = error + 1;
	int attempts = 1;

	do
	{
		result_previous = result;
		result = monte_carlo_volume_by_attempts(f, ranges, attempts);

		if (result == result_previous)
			break;

		error_numeric_method = monte_carlo_volume_error(f, ranges, attempts);
		attempts++;
	} while (error_numeric_method > error);

	return result;
}

double NumericMethod::midpoint_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions)
{
	return pow((range.b - range.a) / divisions, 3) / 24 * df_dx_2(f, (range.b - range.a) / 2);
}

double NumericMethod::trapezoidal_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions)
{
	return -(pow((range.b - range.a) / divisions, 3) / 12) * df_dx_2(f, (range.b - range.a) / 2);
}

double NumericMethod::simpson_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions)
{
	return -(pow((range.b - range.a) / divisions, 5) / 90) * df_dx_4(f, (range.b - range.a) / 2);
}

double NumericMethod::monte_carlo_error(std::function<double(double)> f, IntegrateRange<double> range, int attempts)
{
	random_device rd;
	mt19937 eng(rd());
	uniform_real_distribution<double> distr_x(range.a, range.b);

	double f_error_square_result = 0.0;
	double f_error_result = 0.0;
	int count = 0;

	while (count < attempts)
	{
		double x = distr_x(eng);
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

void NumericMethod::test_numeric_square()
{
	int divisions = 4;
	double error_rate = 0.05;
	Equations* eq = new Equations();
	IntegrateRange<double> range_default = IntegrateRange<double>(0, 1);

	cout << "Error rate: " << error_rate << endl;
	cout << endl;

	cout << "f(x) = e^x" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), std::bind(&NumericMethod::midpoint_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), std::bind(&NumericMethod::simpson_error, this, _1, _2, _3), error_rate) << endl;
	cout << endl;

	cout << "f(x) = square(1-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), std::bind(&NumericMethod::midpoint_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), std::bind(&NumericMethod::simpson_error, this, _1, _2, _3), error_rate) << endl;
	cout << endl;

	cout << "f(x) = e^(-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), std::bind(&NumericMethod::midpoint_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Trapezoidal: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), std::bind(&NumericMethod::trapezoidal_error, this, _1, _2, _3), error_rate) << endl;
	cout << "Simpson: " << numeric_square_by_error_rate(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), std::bind(&NumericMethod::simpson_error, this, _1, _2, _3), error_rate) << endl;
}

void NumericMethod::test_monte_carlo()
{
	int attempts = 10;
	double error_rate = 0.05;
	Equations* eq = new Equations();
	IntegrateRange<double> range_default = IntegrateRange<double>(0, 1);
	IntegrateRange<double> ranges[3];
	ranges[0] = IntegrateRange<double>(1.0, 4.0);
	ranges[1] = IntegrateRange<double>(-3.0, 4.0);
	ranges[2] = IntegrateRange<double>(-1.0, 1.0);


	cout << endl;
	cout << "Attempts: " << attempts << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_1, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = square(x + square(x)): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_volume_by_attempts(std::bind(&Equations::class_6_f_3, eq, _1, _2, _3), ranges, attempts) << endl;

	cout << endl;
	attempts = 100;
	cout << "Attempts: " << attempts << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_1, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = square(x + square(x)): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_volume_by_attempts(std::bind(&Equations::class_6_f_3, eq, _1, _2, _3), ranges, attempts) << endl;

	cout << endl;
	attempts = 1000;
	cout << "Attempts: " << attempts << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_1, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = square(x + square(x)): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_volume_by_attempts(std::bind(&Equations::class_6_f_3, eq, _1, _2, _3), ranges, attempts) << endl;

	cout << endl;
	attempts = 10000;
	cout << "Attempts: " << attempts << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_1, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = square(x + square(x)): " << monte_carlo_by_attempts(std::bind(&Equations::class_6_f_2, eq, _1), range_default, attempts) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_volume_by_attempts(std::bind(&Equations::class_6_f_3, eq, _1, _2, _3), ranges, attempts) << endl;

	/*cout << "Error rate: " << error_rate << endl;
	cout << endl;
	cout << "f(x) = 4 / (1 + x^2): " << monte_carlo_by_error_rate(std::bind(&Equations::class_6_f_1, eq, _1), range_default, error_rate) << endl;
	cout << "f(x) = z^2 + (square(x^2 + y^2) - 3)^2: " << monte_carlo_volume_error_rate(std::bind(&Equations::class_6_f_2, eq, _1, _2, _3), ranges, error_rate) << endl;*/
}

void NumericMethod::test_monte_carlo_distributed()
{
	int attempts = 10000;
	Equations* eq = new Equations();
	IntegrateRange<double> range_default = IntegrateRange<double>(0, 1);
	IntegrateRange<double> ranges[3];
	ranges[0] = IntegrateRange<double>(1.0, 4.0);
	ranges[1] = IntegrateRange<double>(-3.0, 4.0);
	ranges[2] = IntegrateRange<double>(-1.0, 1.0);

	//monte_carlo_by_attempts_distributed(std::bind(&Equations::class_6_f_1, eq, _1), range_default, attempts);
	//monte_carlo_by_attempts_distributed(std::bind(&Equations::class_6_f_2, eq, _1), range_default, attempts);
	monte_carlo_volume_by_attempts_distributed(std::bind(&Equations::class_6_f_3, eq, _1, _2, _3), ranges, attempts);
}

void NumericMethod::test_numeric_square_distributed()
{
	int divisions = 1000000;
	Equations* eq = new Equations();
	IntegrateRange<double> range_default = IntegrateRange<double>(0, 1);

	cout << "Divisions: " << divisions << endl;
	cout << endl;

	cout << "f(x) = e^x" << endl;
	cout << "Midpoint: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Midpoint DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Simpson: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
	cout << "Simpson DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_1, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
	cout << endl;

	cout << "f(x) = square(1-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Midpoint DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Simpson: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
	cout << "Simpson DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_2, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
	cout << endl;

	cout << "f(x) = e^(-x^2)" << endl;
	cout << "Midpoint: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Midpoint DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::midpoint, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Trapezoidal DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::trapezoidal, this, _1, _2), divisions) << endl;
	cout << "Simpson: " << numeric_square_by_divisions(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
	cout << "Simpson DIST: " << numeric_square_by_divisions_distributed(std::bind(&Equations::class_5_f_3, eq, _1), range_default, std::bind(&NumericMethod::simpson, this, _1, _2), divisions) << endl;
}
