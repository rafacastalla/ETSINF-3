#include <stdio.h>
#include <stdlib.h>
#include "sacarpid.h"

int main(int argc, char *argv[]) {

  if(argc ==1){
    printf("Introduce un PID válido por argumento\n");
  }
  else{
      int pid = atoi(argv[1]);
      printf("El PID introducido es %d\n", pid);
      printf("El kernel dice que está en la posición %d\n", sacarpid(pid));
  }
}
