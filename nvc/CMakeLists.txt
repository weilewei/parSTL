# nvc++ -w -fast -Mnouniform -Mfprelaxed -stdpar=gpu -std=c++11 -DUSE_MPI=0 stdPar.cpp -o stdPar
set(CMAKE_CXX_COMPILER "nvc++")
set(CMAKE_C_COMPILER "nvc")
set(CMAKE_CXX_FLAGS "-w -fast -Mnouniform -Mfprelaxed -stdpar=gpu -std=c++11 -DUSE_MPI=0")

add_executable(nvcPar nvcPar.cpp)
