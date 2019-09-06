#include <iostream>
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
};

#endif
