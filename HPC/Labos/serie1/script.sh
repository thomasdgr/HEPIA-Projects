#!/bin/sh
#SBATCH --job-name=exo
#SBATCH --output=exo.o%j
#SBATCH --ntasks=8
#SBATCH --partition=debug-cpu
#SBATCH --time=00:05:00

echo $SLURM_NODELIST

srun ./a.out
