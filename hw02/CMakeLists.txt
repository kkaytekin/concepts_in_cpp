cmake_minimum_required(VERSION 3.14)
find_package(doctest REQUIRED)

project(hw02)

set(EXECUTABLE_NAME runhw02)

# this one wont work here because it needs to be in the CMakeLists.txt at the top
# but we cannot do that too because it will break the assesment pipeline so use
# cmake .. -DCMAKE_CXX_COMPILER=g++-11 instead.
# set compiler as g++-11
# set(CMAKE_CXX_COMPILER "/usr/bin/g++-11" CACHE STRING "C++ compiler" FORCE)

set(CMAKE_CXX_STANDARD 20)

find_package(doctest REQUIRED)

# Making a library
add_library(hw02 STATIC combinatorics.cpp)
# Add include directory
target_include_directories(hw02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Create the executable
add_executable(${EXECUTABLE_NAME} run.cpp)
# Link the library hw02 into runhw02
target_link_libraries(${EXECUTABLE_NAME} PRIVATE hw02)

#target_link_directories(${EXECUTABLE_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(${EXECUTABLE_NAME} doctest)
#target_link_libraries(combinatorics PUBLIC hw02)