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

using namespace std;
using namespace std::placeholders;

int main()
{
	Equations* eq = new Equations();
	NumericMethod num_met = NumericMethod(0, 1, std::bind(&Equations::class_4_f_1, eq, _1));
	
	num_met.test_gradient();

	cout << "Midpoint: " << num_met.Midpoint() << endl;
	cout << "Trapezoidal: " << num_met.Trapezoidal() << endl;
	cout << "Simpson: " << num_met.Simpson() << endl;

	system("pause");
	return 0;
}






