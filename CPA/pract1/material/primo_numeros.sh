#!/bin/sh
#PBS -l nodes=1,walltime=00:05:00
#PBS -q cpa
#PBS -d .
time OMP_NUM_THREADS=4 OMP_SCHEDULE=static ./primo_numeros
