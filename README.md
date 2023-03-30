# C++ Parallel Algorithms Benchmark

This is a brief evaluation of parallel algorithms in C++. The main focus is on parallel
transform and sort algorithms, which are available in several parallel frameworks
such as Intel HPX, Kokkos, TBB, gnu, and nvhpc. To conduct the benchmark, a
vector of random numbers is first allocated and then subjected to a range of parallel
algorithms. The primary objective of the benchmark is to gain valuable insights
into the performance of different parallel algorithms and frameworks.

## Example code

* Standard C++ parallel transform and NVC++ parallel transform

```cpp
std::transform(std::execution::seq, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });

std::transform(std::execution::par, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });

std::transform(std::execution::par_unseq, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });
```

* HPX parallel transform

```cpp
hpx::transform(hpx::execution::seq, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });
hpx::transform(hpx::execution::par, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });
hpx::transform(hpx::execution::par_unseq, workVec.begin(), workVec.end(),
    workVec.begin(), [](double arg){ return std::tan(arg); });
```

* Kokkos parallel transform

```cpp
Kokkos::parallel_for("kokkos::parallel_for transform optimized version", 
  Kokkos::RangePolicy<Kokkos::IndexType<int>, Kokkos::Schedule<Kokkos::Dynamic>>
  (0, length), KOKKOS_LAMBDA (const int& i) {
    workVec(i) = std::tan(workVec(i));
});
```

* GNU parallel transform

```cpp
__gnu_parallel::transform(workVec.begin(), workVec.end(), 
    workVec.begin(), [](double arg){ return std::tan(arg); });
```

* Taskflow parallel transform

```cpp
tf::Executor executor(num_threads);

tf::Taskflow t1;
t1.for_each(workVec.begin(), workVec.end(), [] (double& arg) {
    arg = std::tan(arg);});
```

## How to Build

Example build script:

```shell

module load gcc/11.2.0
module load cmake/3.20.4

cd $HOME
git clone https://github.com/weilewei/parSTL.git
cd parSTL
mkdir build && cd build

cmake \
    -DTBB_DIR=$HOME/install/oneTBB/lib64/cmake/TBB/ \
    -DHPX_DIR=$HOME/install/hpx_gcc_Release/lib64/cmake/HPX/ \
    -DKokkos_DIR=$HOME/kokkos_gcc_openmp/lib64/cmake/Kokkos/ \
    -DNVCXX=/opt/nvidia/hpc_sdk/Linux_x86_64/22.9/compilers/bin/nvc++ \
    ..

make 
```

## How to Run

```shell
for SIZE in 100000000
do
    echo "running stdParTbb_gcc with $SIZE workload"
    ./stdParTbb_gcc $SIZE

    echo "running stdParTbb_clang with $SIZE workload"
    ./stdParTbb_clang $SIZE

    for NUM_THREADS in 1 2 4 8 16 32 64 128
    do
        echo "running nvcPar_cpu with $SIZE workload and $NUM_THREADS threads"
        OMP_NUM_THREADS=$NUM_THREADS OMP_PROC_BIND=spread OMP_PLACES=threads 
        ./nvcPar_cpu $SIZE
    
        echo "running hpxPar_gcc with $SIZE workload and $NUM_THREADS"
        ./hpxPar_gcc $SIZE --hpx:threads=$NUM_THREADS
    
        echo "running hpxPar_clang with $SIZE workload and $NUM_THREADS"
        ./hpxPar_clang $SIZE --hpx:threads=$NUM_THREADS
    
        echo "running gnuPar_gcc with $SIZE workload and $NUM_THREADS"
        OMP_NUM_THREADS=$NUM_THREADS OMP_PROC_BIND=spread OMP_PLACES=threads 
        ./gnuPar_gcc $SIZE 
    
        echo "running gnuPar_clang with $SIZE workload and $NUM_THREADS"
        OMP_NUM_THREADS=$NUM_THREADS OMP_PROC_BIND=spread OMP_PLACES=threads 
        ./gnuPar_clang $SIZE 
    
        echo "running kokkosPar_openmp_gcc with $SIZE workload and $NUM_THREADS"
        OMP_PROC_BIND=spread OMP_PLACES=threads ./kokkosPar_openmp_gcc $SIZE --kokkos-num-threads=$NUM_THREADS
    
        echo "running kokkosPar_threads_gcc with $SIZE workload and $NUM_THREADS"
        ./kokkosPar_threads_gcc $SIZE --kokkos-num-threads=$NUM_THREADS
    
        echo "running kokkosPar_openmp_clang with $SIZE workload and $NUM_THREADS"
        OMP_PROC_BIND=spread OMP_PLACES=threads ./kokkosPar_openmp_clang $SIZE --kokkos-num-threads=$NUM_THREADS
    
        echo "running kokkosPar_threads_clang with $SIZE workload and $NUM_THREADS"
        ./kokkosPar_threads_clang $SIZE --kokkos-num-threads=$NUM_THREADS
    
        echo "running taskflowPar_gcc with $SIZE workload and $NUM_THREADS"
        ./taskflowPar_gcc $SIZE $NUM_THREADS
    
        echo "running taskflowPar_clang with $SIZE workload and $NUM_THREADS"
        ./taskflowPar_clang $SIZE $NUM_THREADS
        done

done 
```
