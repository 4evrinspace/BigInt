cmake_minimum_required(VERSION 3.10)
project(LongNumber)
set(CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE SOURCES "Source/LongNumber.cpp")
add_library(LongNumber SHARED ${SOURCES})
target_include_directories(LongNumber PUBLIC Include)

add_executable(main main.cpp)
target_link_libraries(main LongNumber)