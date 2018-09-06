#!/bin/sh
#PBS -l nodes=1,walltime=00:10:00
#PBS -q cpa
#PBS -d . 
OMP_NUM_THREADS=2 ./o