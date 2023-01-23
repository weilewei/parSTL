cmake_minimum_required(VERSION 3.20.4)
project(kokkosPar LANGUAGES CXX)
find_package(Kokkos REQUIRED)

if (KOKKOS_FOUND)
  include_directories(${KOKKOS_INCLUDE_DIRS})
endif()

add_executable(kokkosPar kokkosPar.cpp)
target_link_libraries(kokkosPar Kokkos::kokkos)