# gcc gnuPar.cpp -lstdc++ -fopenmp -lm -o gnuPar 
#set(CMAKE_C_FLAGS "lstdc++ -O0 -fopenmp -lm -D_GLIBCXX_PARALLEL")

add_executable(gnuPar gnuPar.cpp)
set_source_files_properties( gnuPar.cpp PROPERTIES COMPILE_FLAGS "-lstdc++ -fopenmp -lm " )
target_link_libraries(gnuPar PRIVATE "-lstdc++ -fopenmp -lm")
