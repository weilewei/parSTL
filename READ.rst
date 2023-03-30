# C++ Parallel Algorithms Benchmark

This is a brief evaluation of parallel algorithms in C++. The main focus is on parallel
transform and sort algorithms, which are available in several parallel frameworks such as
Intel HPX, Kokkos, TBB, gnu, and nvhpc. To conduct the benchmark, a vector of random numbers is
first allocated and then subjected to a range of parallel algorithms. The primary objective of
the benchmark is to gain valuable insights into the performance of different parallel algorithms
and frameworks.

# How to Build
Example build script:
``` bash
module load gcc/11.2.0
module load cmake/3.20.4

cd $HOME
git clone https://github.com/weilewei/parSTL.git
cd parSTL
mkdir build && cd build

cmake \
    -DTBB_DIR=/global/homes/w/wwei/install/oneTBB/lib64/cmake/TBB/ \
    -DHPX_DIR=/global/homes/w/wwei/install/hpx_gcc_Release/lib64/cmake/HPX/ \
    -DKokkos_DIR=/global/homes/w/wwei/install/kokkos_gcc_openmp/lib64/cmake/Kokkos/ \
    -DNVCXX=/opt/nvidia/hpc_sdk/Linux_x86_64/22.9/compilers/bin/nvc++ \
    ..

make 
```