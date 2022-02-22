#!/bin/sh
#SBATCH --job-name=results/app
#SBATCH --output=app.o%j
#SBATCH --constraint=GOLD-6240
#SBATCH --time=08:00:00

echo $SLURM_NODELIST
srun ./laplace.out $1 $2 $3 