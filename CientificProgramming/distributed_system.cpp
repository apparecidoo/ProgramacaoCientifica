#include "pch.h"
#include "distributed_system.h"

DistributedSystem::DistributedSystem()
{
}

DistributedSystem::~DistributedSystem()
{
}

void DistributedSystem::mpi_hello_world()
{
	double h;
	int i;
	int id;
	int ierr;
	int master = 0;
	int n;
	int n_part;
	int p;
	double q;
	double q_diff;
	double q_exact = 3.141592653589793238462643;
	double q_part;
	double wtime_diff;
	double wtime_end;
	double wtime_start;
	double x;
	/*
	  Initialize MPI.
	*/
	ierr = MPI_Init(NULL, NULL);

	if (ierr != 0)
	{
		printf("\n");
		printf("QUADRATURE_MPI - Fatal error!\n");
		printf("  MPI_Init returns nonzero IERR.\n");
		exit(1);
	}
	/*
	  Get the number of processes.
	*/
	ierr = MPI_Comm_size(MPI_COMM_WORLD, &p);
	/*
	  Determine this processes's rank.
	*/
	ierr = MPI_Comm_rank(MPI_COMM_WORLD, &id);
	/*
	  Say hello.
	*/
	if (id == master)
	{
		printf("\n");
		printf("QUADRATURE - Master process:\n");
		printf("  C version\n");
		printf("\n");
		printf("  An MPI example program.\n");
		printf("  Estimate the value of PI by approximating an integral.\n");
		printf("  The integral is approximated by a sum,\n");
		printf("  whose calculation is divided among a number of processes.\n");
		printf("\n");
		printf("  Compiled on %s at %s.\n", __DATE__, __TIME__);
		printf("\n");
		printf("  The number of processes available is %d.\n", p);
	}
	/*
	  Record the starting time.
	*/
	if (id == master)
	{
		wtime_start = MPI_Wtime();
	}
	/*
	  We could assume that the number of intervals N is read in by process 0.
	  To keep this program simple, we'll just assign a value to
	  N, but only on process 0.
	*/
	if (id == master)
	{
		n = 1000;
		printf("\n");
		printf("QUADRATURE - Master process:\n");
		printf("  Number of intervals used is %d.\n", n);
	}
	/*
	  The master process broadcasts, and the other processes receive, the number of intervals N.
	*/
	ierr = MPI_Bcast(&n, 1, MPI_INT, master, MPI_COMM_WORLD);
	/*
	  Every process integrates F(X) over a subinterval determined by its process ID.
	*/
	h = 1.0 / (double)n;

	q_part = 0.0;
	n_part = 0;

	for (i = id + 1; i <= n; i = i + p)
	{
		x = (double)(2 * i - 1)
			/ (double)(2 * n);

		n_part = n_part + 1;
		q_part = q_part + f(x);
	}
	q_part = q_part * h;

	printf("\n");
	printf("QUADRATURE - Process %d:\n", id);
	printf("  Points used = %d\n", n_part);
	printf("  Estimate %f.\n", q_part);
	/*
	  Each process sends its local result Q_PART to the MASTER process,
	  to be added to the global result QI.
	*/
	ierr = MPI_Reduce(&q_part, &q, 1, MPI_DOUBLE, MPI_SUM, master, MPI_COMM_WORLD);
	/*
	  The master process scales the sum and reports the results.
	*/
	if (id == master)
	{
		printf("\n");
		printf("QUADRATURE - Master process:\n");
		printf("  Integral estimate      %24.16f\n", q);
		printf("  The exact value is     %24.16f\n", q_exact);
		q_diff = fabs(q - q_exact);
		printf("  The error is           %24.16f\n", q_diff);

		wtime_end = MPI_Wtime();
		wtime_diff = wtime_end - wtime_start;

		printf("\n");
		printf("  Wall clock elapsed seconds = %f\n", wtime_diff);
	}
	/*
	  Terminate MPI.
	*/
	ierr = MPI_Finalize();
	/*
	  Terminate.
	*/
	if (id == master)
	{
		printf("\n");
		printf("QUADRATURE - Master process:\n");
		printf("  Normal end of execution.\n");
		printf("\n");
	}
}

double DistributedSystem::f(double x)
{
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);

	// Get the number of processes
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	// Print off a hello world message
	printf("Hello world from processor %s, rank %d out of %d processors\n",
		processor_name, world_rank, world_size);

	// Finalize the MPI environment.
	MPI_Finalize();

	return 0.0;
}