#!/bin/bash

#SBATCH -A nstaff

#SBATCH -C gpu
#SBATCH -t 30:00
#SBATCH -N 1
#SBATCH --ntasks-per-node=1

#SBATCH -o parSTL.out
#SBATCH -e parSTL.err

cd /global/homes/w/wwei/src/parSTL
./scripts.sh
