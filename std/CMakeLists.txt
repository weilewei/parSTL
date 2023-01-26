find_package(OpenMP)

add_executable(stdPar stdPar.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(stdPar PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(stdPar PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")