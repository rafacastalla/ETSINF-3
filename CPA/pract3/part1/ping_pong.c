#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 

int main(int argc,char *argv[]) 
{ 
  int    n, tambyte, myid, numprocs, i; 
  double aux, tmp; 

  MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&myid); 

  if (argc == 3){
    tambyte = atoi(argv[1]);
    n = atoi(argv[2]);
  }else {
    n = 100;
    tambyte = 1;
  }

  char byte[tambyte];
  
  if (n<=0) MPI_Abort(MPI_COMM_WORLD,MPI_ERR_ARG);

  for(i = 0; i < n; i++){
    if (myid==0) {
      aux = MPI_Wtime();
      MPI_Send(byte, tambyte, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
      MPI_Recv(byte, tambyte, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      tmp += MPI_Wtime() - aux;
    }else{
      MPI_Recv(byte, tambyte, MPI_CHAR, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(byte, tambyte, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
    }
  }

  if (myid==0) {
    printf("Cálculo del tiempo entre mensages con %d procesos\n", numprocs); 
    printf("Tiempo: %f\n", tmp/n); 
  }

  MPI_Finalize(); 
  return 0; 
} 

