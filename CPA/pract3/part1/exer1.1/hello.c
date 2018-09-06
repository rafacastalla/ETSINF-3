#include <stdio.h>
#include <mpi.h>

int main (int argc, char *argv[])
{
	int rank, size;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Get the name of the processor
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);
	printf("Hello world from process %d of %d, el procesador es %d\n", rank, size,name_len);
	MPI_Finalize();
	return 0;
}
