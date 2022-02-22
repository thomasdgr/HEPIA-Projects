#!/bin/sh

#SBATCH --job-name=app
#SBATCH --output=results/output_%j
#SBATCH --time=0-12:00:00
#SBATCH --partition=shared-gpu
#SBATCH --nodelist=gpu024
#SBATCH --gpus=1
#SBATCH --mem=10G
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=3

~/projet2/src/laplace_gpu.out $1 $2 $3 $4 $5 $6 $7