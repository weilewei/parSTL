cmake_minimum_required(VERSION 3.20.3)
project(parSTL LANGUAGES CXX C)

set(CMAKE_BUILD_TYPE Release)

set(HPX_DIR "/global/homes/w/wwei/install/hpx_Release/lib64/cmake/HPX/")
set(Kokkos_DIR "/global/homes/w/wwei/install/kokkos_cpu/lib64/cmake/Kokkos/")
set(TBB_DIR "/global/u2/w/wwei/src/spack/opt/spack/linux-sles15-zen3/gcc-11.2.0/intel-tbb-2021.7.0-2ls74bj4nkv3twgy2e5mn4xa4ovpyl6z/lib64/cmake/TBB/")

include_directories(commons)

add_subdirectory(std)
add_subdirectory(hpx)
add_subdirectory(kokkos)
# add_subdirectory(nvc)
add_subdirectory(gnu)

