cmake_minimum_required(VERSION 3.10)
project(HomeWork)
set(CMAKE_CXX_STANDARD 11)


#setting vars
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -O2")
#adding library and include file to library
add_library(LongNumber SHARED Source/LongNumber.cpp)
target_include_directories(LongNumber PUBLIC Include)

add_executable(pi pi.cpp)
add_executable(arithmetic arithmetic.cpp)
add_executable(comparision comparision.cpp)
add_executable(constructors constructors.cpp)
#Link longnumber to tests and main
target_link_libraries(pi LongNumber)
target_link_libraries(arithmetic LongNumber)
target_link_libraries(comparision LongNumber)
target_link_libraries(constructors LongNumber)

