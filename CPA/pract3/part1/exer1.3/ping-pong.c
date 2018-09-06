/* Ping-pong program */

#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define NMAX 1000000
#define NREPS 100

char buf[NMAX];

int main(int argc,char *argv[]) 
{ 
	int n, myid, numprocs numvegades; 

	MPI_Init(&argc,&argv); 
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
	MPI_Comm_rank(MPI_COMM_WORLD,&myid); 

	/* The program takes 1 argument: message size (n), with a default size of 100 
	 bytes and a maximum size of NMAX bytes*/
	if (argc>=2) n = atoi(argv[1]);
	else n = 100;
	if (argc==3) numvegades = atoi(argv[2]);
	else numvegades = 100;

	if (n<0 || n>NMAX) n=NMAX;
		for(i=0;i<numvegades;i++){
			/* COMPLETE: get current time (with MPI_Wtime) */
			double t1 = MPI_Wtime();
			/* COMPLETE: loop of NREPS iterations. 
				 In each iteration, P0 sends a message of n bytes to P1, and P1 sends the same 
				 message back to P0. The data sent is taken from array buf and received into
				 the same array */
			if(myid !=0){
				MPI_Recv(&n, 0, MPI_INT,0,1,MPI_COMM_WORLD);
				MPI_Send(&n, 0, MPI_INT,0,1,MPI_COMM_WORLD);
			}else{
				MPI_Send(&n, 1, MPI_INT,0,1,MPI_COMM_WORLD);
				MPI_Recv(&n, 1, MPI_INT,0,1,MPI_COMM_WORLD);
			}
		  


			/* COMPLETE: get current time (with MPI_Wtime) */
			double t2 = MPI_Wtime();
		}
	
	/* COMPLETE: compute the time of transmission of a single message (in milliseconds) 
	and print it (only one message should be printed) */

	MPI_Finalize(); 
	return 0; 
} 

