find_package(Kokkos REQUIRED)

if (KOKKOS_FOUND)
  include_directories(${KOKKOS_INCLUDE_DIRS})
endif()

add_executable(kokkosPar kokkosPar.cpp)
target_link_libraries(kokkosPar Kokkos::kokkos)
target_include_directories(kokkosPar PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")    

# add_executable(kokkosBenchmark kokkosBenchmark.cpp)
# target_link_libraries(kokkosBenchmark Kokkos::kokkos)