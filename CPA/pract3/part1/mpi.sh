#!/bin/sh
#PBS -l nodes=10,walltime=00:10:00
#PBS -q cpa
#PBS -d .

mpiexec exe 