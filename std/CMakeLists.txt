find_package(OpenMP)
find_package(TBB)

add_executable(stdPar stdPar.cpp)

target_link_libraries(stdPar PUBLIC OpenMP::OpenMP_CXX TBB::tbb)

target_include_directories(stdPar PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")