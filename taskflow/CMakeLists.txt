find_package (Threads REQUIRED)

add_executable(taskflowPar taskflowPar.cpp)
target_link_libraries (taskflowPar ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(taskflowPar PRIVATE "${CMAKE_CURRENT_LIST_DIR}/commons" "${CMAKE_CURRENT_SOURCE_DIR}/include")    
