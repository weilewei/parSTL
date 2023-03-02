#!/bin/bash

#SBATCH -A nstaff

#SBATCH -C gpu
#SBATCH -t 30:00
#SBATCH -q regular
#SBATCH -N 1
#SBATCH --ntasks-per-node=1

#SBATCH -o stdpar3.out
#SBATCH -e stdpar3.err

# for SIZE in 100000 1000000 10000000 100000000
for SIZE in 100000000
do
	# echo "running stdParTbb_gcc with $SIZE workload"
	# ./stdParTbb_gcc $SIZE

	# echo "running stdParTbb_clang with $SIZE workload"
	# ./stdParTbb_clang $SIZE

	# echo "running nvcPar_cpu with $SIZE workload"
	# ./nvcPar_cpu $SIZE

	# echo "running nvcPar_gpu with $SIZE workload"
	# ./nvcPar_gpu $SIZE

	for NUM_THREADS in 1 2 4 8 16 32 64 128
	# for NUM_THREADS in 128
	do
		# echo "running hpxPar_gcc with $SIZE workload and $NUM_THREADS"
		# ./hpxPar_gcc $SIZE --hpx:threads=$NUM_THREADS

		# echo "running hpxPar_clang with $SIZE workload and $NUM_THREADS"
		# ./hpxPar_clang $SIZE --hpx:threads=$NUM_THREADS

		# echo "running gnuPar_gcc with $SIZE workload and $NUM_THREADS"
		# OMP_NUM_THREADS=$NUM_THREADS OMP_PROC_BIND=spread OMP_PLACES=threads ./gnuPar_gcc $SIZE 

		# echo "running gnuPar_clang with $SIZE workload and $NUM_THREADS"
		# OMP_NUM_THREADS=$NUM_THREADS OMP_PROC_BIND=spread OMP_PLACES=threads ./gnuPar_clang $SIZE 

		# echo "running kokkosPar_openmp_gcc with $SIZE workload and $NUM_THREADS"
		# OMP_PROC_BIND=spread OMP_PLACES=threads ./kokkosPar_openmp_gcc $SIZE --kokkos-num-threads=$NUM_THREADS

		# echo "running kokkosPar_threads_gcc with $SIZE workload and $NUM_THREADS"
		# ./kokkosPar_threads_gcc $SIZE --kokkos-num-threads=$NUM_THREADS

		# echo "running kokkosPar_openmp_clang with $SIZE workload and $NUM_THREADS"
		# OMP_PROC_BIND=spread OMP_PLACES=threads ./kokkosPar_openmp_clang $SIZE --kokkos-num-threads=$NUM_THREADS

		# echo "running kokkosPar_threads_clang with $SIZE workload and $NUM_THREADS"
		# ./kokkosPar_threads_clang $SIZE --kokkos-num-threads=$NUM_THREADS

		echo "running taskflowPar_gcc with $SIZE workload and $NUM_THREADS"
		./taskflowPar_gcc $SIZE $NUM_THREADS

		echo "running taskflowPar_clang with $SIZE workload and $NUM_THREADS"
		./taskflowPar_clang $SIZE $NUM_THREADS
	done

done 


