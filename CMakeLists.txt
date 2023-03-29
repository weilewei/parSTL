cmake_minimum_required(VERSION 3.20.3)
project(parSTL LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Release)

if(HPX_DIR)
    set(HPX_DIR ${HPX_DIR} CACHE PATH "HPX_DIR")
else()
    error("HPX_DIR not set")
endif()

if(Kokkos_DIR)
    set(Kokkos_DIR ${HPX_DIR} CACHE PATH "Kokkos_DIR")
else()
    error("Kokkos_DIR not set")
endif()

# TBB package will be required for stdTbb build 
if(TBB_DIR)
    set(TBB_DIR ${HPX_DIR} CACHE PATH "TBB_DIR")
else()
    error("TBB_DIR not set")
endif()

# nvhpc 22.9 and beyond is recommended 
if(NVCXX)
    set(NVCXX ${NVCXX} CACHE PATH "NVCXX")
else()
    error("NVCXX not set")
endif()

include_directories(commons)

add_subdirectory(stdTbb)
add_subdirectory(hpx)
add_subdirectory(kokkos)
add_subdirectory(gnu)
add_subdirectory(taskflow)
add_subdirectory(nvc)

