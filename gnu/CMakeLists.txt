# gcc gnuPar.cpp -lstdc++ -fopenmp -lm -o gnuPar 
#set(CMAKE_C_FLAGS "lstdc++ -O0 -fopenmp -lm -D_GLIBCXX_PARALLEL")
find_package(OpenMP)

add_executable(gnuPar gnuPar.cpp)
if(OpenMP_CXX_FOUND)
    target_link_libraries(gnuPar PUBLIC OpenMP::OpenMP_CXX)
endif()
set_source_files_properties( gnuPar.cpp PROPERTIES COMPILE_FLAGS "-lstdc++ -fopenmp -lm " )
target_include_directories(gnuPar PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")
