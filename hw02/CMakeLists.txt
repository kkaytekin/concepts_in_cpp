cmake_minimum_required(VERSION 3.14)
find_package(doctest REQUIRED)

project(hw02)

set(EXECUTABLE_NAME runhw02)

set(CMAKE_CXX_STANDARD 20)

find_package(doctest REQUIRED)

# Making a library
add_library(hw02 STATIC combinatorics.cpp)
# Add include directory
target_include_directories(hw02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# Create the executable
add_executable(${EXECUTABLE_NAME} run.cpp)
# Link the library hw02 into runhw02
target_link_libraries(${EXECUTABLE_NAME} PUBLIC hw02)

#target_link_directories(${EXECUTABLE_NAME}  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(${EXECUTABLE_NAME} doctest)
#target_link_libraries(combinatorics PUBLIC hw02)