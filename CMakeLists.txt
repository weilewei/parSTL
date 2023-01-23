cmake_minimum_required(VERSION 3.20.3)
project(parSTL LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_COMPILER "/global/homes/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/gcc-11.2.0-zvvuszlajgsejuuf5o25rceihybuakbo/bin/gcc")
set(CMAKE_CXX_COMPILER "/global/homes/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/gcc-11.2.0-zvvuszlajgsejuuf5o25rceihybuakbo/bin/g++")
set(HPX_DIR "/global/homes/w/wwei/install/hpx_Release/lib64/cmake/HPX/")
set(Kokkos_DIR "/global/homes/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/kokkos-3.7.01-gpowb3o4jdwzu4dvflvyw7jcz7r7man3/lib64/cmake/Kokkos/")

add_subdirectory(std)
add_subdirectory(hpx)
add_subdirectory(kokkos)
add_subdirectory(nvc)