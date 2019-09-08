#include "pch.h"
#include <iostream>
#include <chrono>
#include <functional>

#include "custom_exception.h"
#include "linked_list.h"
#include "stack.h"
#include "stack_dynamic.h"
#include "queue.h"
#include "queue_dynamic.h"
#include "puzzle.h"
#include "numeric_method.h"
#include "equations.h"
#include "distributed_system.h"

using namespace std;
using namespace std::placeholders;

int main()
{
	Equations* eq = new Equations();
	NumericMethod num_met = NumericMethod();
	
	//num_met.test_gradient();

	num_met.test_adaptative_square();

	//num_met.test_monte_carlo();

	//DistributedSystem().mpi_hello_world();

	system("pause");
	return 0;
}