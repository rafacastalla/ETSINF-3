#!/bin/sh
#PBS -l nodes=2,walltime=00:10:00
#PBS -q cpa
#PBS -d .
cat $PBS_NODEFILE
mpiexec ./newtonMod -c4 -r0.01 -x0.1 -y0.2
