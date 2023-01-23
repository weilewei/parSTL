find_package(HPX REQUIRED)

if (HPX_FOUND)
  include_directories(${HPX_INCLUDE_DIRS})
endif()

add_executable(hpxPar hpxPar.cpp)
target_link_libraries(hpxPar PUBLIC HPX::hpx HPX::wrap_main HPX::iostreams_component)