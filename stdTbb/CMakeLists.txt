find_package(TBB REQUIRED tbb)
add_executable(stdParTbb stdParTbb.cpp)
target_link_libraries(stdParTbb PUBLIC TBB::tbb) 
target_include_directories(stdParTbb PRIVATE "${CMAKE_SOURCE_DIR}/commons")
