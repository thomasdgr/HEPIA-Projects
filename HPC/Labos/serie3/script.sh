#!/bin/sh
#SBATCH --job-name=app
#SBATCH --output=app.o%j
##SBATCH --ntasks=8
#SBATCH --partition=debug-cpu
#SBATCH --time=00:05:00

srun ./a.out $1