cmake_minimum_required(VERSION 3.10)
project(HomeWork)
set(CMAKE_CXX_STANDARD 11)


#setting vars
set(GCC_COMPILE_OPTIONS "-Wall -O2")
#adding library and include file to library
add_library(LongNumber SHARED Source/LongNumber.cpp)
target_include_directories(LongNumber PUBLIC Include)

add_executable(main main.cpp)
#Link longnumber to main
target_link_libraries(main LongNumber)

target_compile_options(main PUBLIC "$<$<CONFIG:DEBUG>:${GCC_COMPILE_OPTIONS}>")

