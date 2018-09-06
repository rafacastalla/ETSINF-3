#!/bin/sh
#PBS -l nodes=2,walltime=00:10:00
#PBS -q cpa
#PBS -d .
cat $PBS_NODEFILE
mpiexec ./newton -c5
