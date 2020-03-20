#include <iostream>
# include <math.h>
# include <mpi.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
#include "numeric_method.h"
#include "equations.h"

#ifndef DISTRIBUTED_SYSTEM_H
#define DISTRIBUTED_SYSTEM_H

using namespace std;

class DistributedSystem {

public:
	DistributedSystem();
	~DistributedSystem();

	void mpi_hello_world();
	double f(double x);
};

#endif
