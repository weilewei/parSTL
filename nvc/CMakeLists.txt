set(CMAKE_CXX_COMPILER ${NVCXX})

set(CMAKE_CXX_FLAGS "-w -fast -Mnouniform -Mfprelaxed -stdpar=multicore -std=c++11 -DUSE_MPI=0 --gcc-toolchain=/opt/cray/pe/gcc/11.2.0/bin/")
add_executable(nvcParMulticore nvcPar.cpp)
target_include_directories(nvcParMulticore PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")    

set(CMAKE_CXX_FLAGS "-w -fast -Mnouniform -Mfprelaxed -stdpar=gpu -std=c++11 -DUSE_MPI=0")
add_executable(nvcParGpu nvcPar.cpp)
target_include_directories(nvcParGpu PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons")    
