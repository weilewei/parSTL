cmake_minimum_required(VERSION 3.20.3)
project(parSTL LANGUAGES CXX C)

set(CMAKE_BUILD_TYPE Release)

# set(TBB_DIR "/global/homes/w/wwei/install/oneTBB/lib64/cmake/TBB/")
# set(HPX_DIR "/global/homes/w/wwei/install/hpx_gcc_Release/lib64/cmake/HPX/")
# # set(Kokkos_DIR "/global/homes/w/wwei/install/kokkos_gcc_openmp/lib64/cmake/Kokkos/")
# set(Kokkos_DIR "/global/homes/w/wwei/install/kokkos_gcc_threads/lib64/cmake/Kokkos/")

# set(HPX_DIR "/global/homes/w/wwei/install/hpx_clang_Release/lib64/cmake/HPX/")
# set(Kokkos_DIR "/global/homes/w/wwei/install/kokkos_clang_threads//lib64/cmake/Kokkos/")
# # set(Kokkos_DIR "/global/homes/w/wwei/install/kokkos_clang_openmp//lib64/cmake/Kokkos/")
# set(TBB_DIR "/global/homes/w/wwei/install/oneTBB_clang/lib64/cmake/TBB/")

include_directories(commons)

add_subdirectory(stdTbb)
add_subdirectory(hpx)
add_subdirectory(kokkos)
# add_subdirectory(nvc)
add_subdirectory(gnu)
add_subdirectory(taskflow)

