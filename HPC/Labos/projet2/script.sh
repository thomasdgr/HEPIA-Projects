#!/bin/sh

#SBATCH --job-name=app
#SBATCH --output=output_%j
#SBATCH --time=0-00:05:00

#SBATCH --partition=shared-gpu

##SBATCH --ntasks=1
##SBATCH --gres=gpu:pascal:1
##SBATCH --cpus-per-task=1

#SBATCH --gpus=1

./$1