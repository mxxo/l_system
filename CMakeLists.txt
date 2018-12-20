cmake_minimum_required(VERSION 2.8.12)
 project(l_system)

 add_definitions("-std=c++17")

 set(GCC_WARN_FLAGS "-Wall -Wextra -Wpedantic")
 #set(GCC_DEBUG_FLAGS "-g")
 set(GCC_MORE_WARN_FLAGS "-Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")
 
 set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_WARN_FLAGS}")
 set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_MORE_WARN_FLAGS}")
 #set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_DEBUG_FLAGS}")
 
 subdirs(src examples)
 